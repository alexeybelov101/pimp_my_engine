#pragma once
#include "../Interfaces/ISolver.hpp"
#include "../Constants/GasDynamics.hpp"
#include <cmath>
#include <algorithm>

namespace GD = GasDynamics;

class HLLCSolver : public ISolver {
public:
    std::pair<Flux, Flux> solve(
        const IBoundary& leftBoundary,
        const IBoundary& rightBoundary
    ) override {
        // Получаем состояния с обеих сторон границы
        Cell leftState = leftBoundary.getState();
        Cell rightState = rightBoundary.getState();

        // Площадь сечения - минимум из двух (для сохранения консервативности)
        double area = std::min(leftBoundary.getArea(), rightBoundary.getArea());

        // Вычисляем поток через границу
        Flux flux = calculateHLLC(leftState, rightState, area);

        // Возвращаем противоположные потоки для каждой стороны
        return { flux, {-flux.mass, -flux.momentum, -flux.energy} };
    }

private:
    Flux calculateHLLC(const Cell& L, const Cell& R, double area) {
        // Извлекаем примитивные переменные из консервативных

        // Левое состояние
        double rhoL = L.rho;
        double uL = (rhoL > 1e-10) ? L.rho_u / rhoL : 0.0;
        double pL = (GD::GAMMA - 1.0) * (L.rho_E - 0.5 * L.rho_u * uL);

        // Правое состояние
        double rhoR = R.rho;
        double uR = (rhoR > 1e-10) ? R.rho_u / rhoR : 0.0;
        double pR = (GD::GAMMA - 1.0) * (R.rho_E - 0.5 * R.rho_u * uR);

        // Защита от отрицательных давлений
        pL = std::max(pL, 1.0);
        pR = std::max(pR, 1.0);

        // Скорость звука
        double aL = std::sqrt(GD::GAMMA * pL / rhoL);
        double aR = std::sqrt(GD::GAMMA * pR / rhoR);

        // Оценки скоростей волн (формула Davis)
        double S_L = std::min(uL - aL, uR - aR);
        double S_R = std::max(uL + aL, uR + aR);

        // Скорость контактного разрыва
        double S_M = (pR - pL + rhoL * uL * (S_L - uL) - rhoR * uR * (S_R - uR))
                     / (rhoL * (S_L - uL) - rhoR * (S_R - uR));

        // Выбираем подходящее состояние для вычисления потока
        Flux flux;

        if (0.0 <= S_L) {
            // Всё течение движется вправо - используем левое состояние
            flux.mass = rhoL * uL * area;
            flux.momentum = (rhoL * uL * uL + pL) * area;
            flux.energy = uL * (L.rho_E + pL) * area;

        } else if (S_L <= 0.0 && 0.0 <= S_M) {
            // Левое звёздное состояние (*L)
            double rho_star = rhoL * (S_L - uL) / (S_L - S_M);
            double u_star = S_M;
            double p_star = pL + rhoL * (S_L - uL) * (S_M - uL);

            // Полная энергия в звёздном состоянии
            double E_star = p_star / ((GD::GAMMA - 1.0) * rho_star) + 0.5 * u_star * u_star;
            double rhoE_star = rho_star * E_star;

            flux.mass = rho_star * u_star * area;
            flux.momentum = (rho_star * u_star * u_star + p_star) * area;
            flux.energy = u_star * (rhoE_star + p_star) * area;

        } else if (S_M <= 0.0 && 0.0 <= S_R) {
            // Правое звёздное состояние (*R)
            double rho_star = rhoR * (S_R - uR) / (S_R - S_M);
            double u_star = S_M;
            double p_star = pR + rhoR * (S_R - uR) * (S_M - uR);

            // Полная энергия в звёздном состоянии
            double E_star = p_star / ((GD::GAMMA - 1.0) * rho_star) + 0.5 * u_star * u_star;
            double rhoE_star = rho_star * E_star;

            flux.mass = rho_star * u_star * area;
            flux.momentum = (rho_star * u_star * u_star + p_star) * area;
            flux.energy = u_star * (rhoE_star + p_star) * area;

        } else {
            // Всё течение движется влево - используем правое состояние
            flux.mass = rhoR * uR * area;
            flux.momentum = (rhoR * uR * uR + pR) * area;
            flux.energy = uR * (R.rho_E + pR) * area;
        }

        return flux;
    }
};
