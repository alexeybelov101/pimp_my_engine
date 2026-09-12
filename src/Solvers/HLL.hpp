#pragma once
#include "../Structs/Cell.hpp"
#include "../Structs/Flux.hpp"
#include "../Constants/GasDynamics.hpp"
#include <cmath>
#include <algorithm>

#include <iostream>

namespace GD = GasDynamics;

namespace Solvers {
    inline Flux HLL(const Cell& L, const Cell& R, double area) {
        if (area == 0.0) { return Flux(); }

        double rhoL = L.rho;
        double uL = (rhoL > 1e-10) ? L.rho_u / rhoL : 0.0;
        double pL = std::max((GD::GAMMA - 1.0) * (L.rho_E - 0.5 * L.rho_u * uL), 1.0);
// std::cout << "rhoL: " << rhoL << std::endl;
// std::cout << "uL: " << uL << std::endl;
// std::cout << "pL: " << pL << std::endl;
        double rhoR = R.rho;
        double uR = (rhoR > 1e-10) ? R.rho_u / rhoR : 0.0;
        double pR = std::max((GD::GAMMA - 1.0) * (R.rho_E - 0.5 * R.rho_u * uR), 1.0);
// std::cout << "rhoR: " << rhoR << std::endl;
// std::cout << "uR: " << uR << std::endl;
// std::cout << "pR: " << pR << std::endl;
        double aL = std::sqrt(GD::GAMMA * pL / rhoL);
        double aR = std::sqrt(GD::GAMMA * pR / rhoR);
// std::cout << "aL: " << aL << std::endl;
// std::cout << "aR: " << aR << std::endl;

        // Оценки скоростей волн (Davis)
        double S_L = std::min(uL - aL, uR - aR);
        double S_R = std::max(uL + aL, uR + aR);
// std::cout << "S_L: " << S_L << std::endl;
// std::cout << "S_R: " << S_L << std::endl;
std::cout << std::endl;

        Flux F_L(rhoL * uL, rhoL * uL * uL + pL, uL * (L.rho_E + pL));
        Flux F_R(rhoR * uR, rhoR * uR * uR + pR, uR * (R.rho_E + pR));

        Flux flux;
        if (0.0 <= S_L) {
            flux = F_L;
        } else if (S_R <= 0.0) {
            flux = F_R;
        } else {
            // HLL формула усреднения
            double denom = S_R - S_L;
            flux.mass = (S_R * F_L.mass - S_L * F_R.mass + S_L * S_R * (rhoR - rhoL)) / denom;
            flux.momentum = (S_R * F_L.momentum - S_L * F_R.momentum + S_L * S_R * (rhoR * uR - rhoL * uL)) / denom;
            flux.energy = (S_R * F_L.energy - S_L * F_R.energy + S_L * S_R * (R.rho_E - L.rho_E)) / denom;
        }

        flux.mass *= area;
        flux.momentum *= area;
        flux.energy *= area;

        return flux;
    }
}
