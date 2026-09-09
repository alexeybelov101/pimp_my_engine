#pragma once
#include "../Interfaces/IBoundary.hpp"
#include "../Structs/Cell.hpp"
#include "../Structs/Flux.hpp"
#include "../Constants/GasDynamics.hpp"
#include <vector>

namespace GD = GasDynamics;

namespace Solvers {
    std::vector<Flux> RhiemannSolver_3x(const std::vector<IBoundary>& boundaries) {
        std::vector<Flux> fluxes(boundaries.size(), Flux());
        return fluxes;
    }
}
