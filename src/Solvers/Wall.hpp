// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Structs/Cell.hpp"
#include "Structs/Flux.hpp"
#include "Constants/GasDynamics.hpp"

namespace GD = GasDynamics;

namespace Solvers {
    inline Flux Wall(const Cell& cell, double A_wall)
    {
        // Извлекаем примитивные переменные
        const double rho = cell.rho;
        const double u = (rho > 1e-10) ? cell.rho_u / rho : 0.0;
        double p = (GD::GAMMA - 1.0) * (cell.rho_E - 0.5 * rho * u * u);

        // p = std::max(p, 1.0);

        const double p_wall = p + rho * u * u;

        return Flux(
            0.0,
            p_wall * A_wall,
            0.0
        );
    }

}
