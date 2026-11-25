// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Coil.hpp"
#include <cmath>

Coil::Coil(
    Winding primary,
    Winding secondary
):
    primary_(primary),
    secondary_(secondary) {
        k_ = 0.98;
        M_ = k_ * std::sqrt(primary.L * secondary.L);
        n_ = static_cast<double>(secondary.turns) / primary.turns;
        Ceq_ = secondary.C + primary.C / (n_ * n_);
    }

void Coil::charge(double dt) {
    isCharging_ = true;
    primary_.U = 12.0;

    const double tau = primary_.L / primary_.R;
    const double steadyCurrent = primary_.U / primary_.R;

    primary_.I = steadyCurrent
        + (primary_.I - steadyCurrent) * std::exp(-dt / tau);
}

double Coil::discharge(double dt, double Ubreak, double Rchain, double Ihold, double Uarc) {
    double Rtotal = Rchain + secondary_.R;
    double result = 0.0;

    if (isCharging_ == true) {
        isCharging_ = false;
        E_ = 0.5 * primary_.L * primary_.I * primary_.I;
        primary_.reset();

        double pUmax = 350; //350В - предельное напряжение обратного тока транзистора коммутатора
        secondary_.U = std::min(std::sqrt(2 * E_ / Ceq_), pUmax * n_);

        if (secondary_.U >= Ubreak) { //грубая проверка на пробой
            double Ebreak = 0.5 * Ceq_ * Ubreak * Ubreak; //полная энергия пробоя
            E_ -= Ebreak;
            result += Ebreak * Rchain / Rtotal; // энергия ёмкостного разряда, ушедшая во внешнюю цепь
            secondary_.I = std::sqrt(2.0 * E_ / secondary_.L); //ток вторички для индуктивной фазы из остатка энергии
        } else {
            E_ = 0.0;
            secondary_.reset();
            return result;
        }
    }

    if (secondary_.I > Ihold) {
        const double Ls = secondary_.L;
        const double tau = Ls / Rtotal;
        const double b = Uarc / Rtotal;

        // Время, за которое ток теоретически упадёт до уровня удержания Ihold
        double tZero = tau * std::log((secondary_.I + b) / (Ihold + b));

        // Реальное время горения в этом шаге (не может превышать dt)
        const double T = std::min(dt, tZero);

        // Ток в конце шага (или в момент гашения)
        double I_next = (secondary_.I + b) * std::exp(-T / tau) - b;
        I_next = std::max(I_next, 0.0);

        // Изменение магнитной энергии за время T
        const double E0 = 0.5 * Ls * secondary_.I * secondary_.I;
        const double E1 = 0.5 * Ls * I_next * I_next;
        const double dE_total = E0 - E1; // Полная энергия, рассеянная во всём Rtotal

        // Доля энергии, ушедшая именно во внешнюю цепь (Rchain)
        result += dE_total * Rchain / Rtotal;

        // Обновляем состояние катушки
        secondary_.I = I_next;
        E_ = E1; // Обновляем остаток магнитной энергии

        // Если ток упал до порога гашения в течение этого шага, гасим искру полностью
        if (T < dt || secondary_.I <= Ihold) {
            secondary_.I = 0.0;
            E_ = 0.0;
        }
    } else {
        // Ток уже ниже порога удержания, искра погасла (или не зажглась)
        secondary_.I = 0.0;
        E_ = 0.0;
    }

    return result;
}
