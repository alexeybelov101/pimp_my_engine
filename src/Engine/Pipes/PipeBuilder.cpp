#include "PipeBuilder.hpp"
#include "Pipe.hpp"
#include "../../Structs/Cell.hpp"
#include "../../Structs/Flux.hpp"
#include "../../Constants/GasDynamics.hpp"

#include <numbers>
#include <cmath>
#include <vector>
#include <nlohmann/json.hpp>

namespace GD = GasDynamics;
using json = nlohmann::json;

constexpr double MM_TO_M = 1.0e-3;

Pipe PipeBuilder::build(const json& config, double dt) {
    double length = config["length"].get<double>() * MM_TO_M;
    double radius = config["radius"].get<double>() * MM_TO_M;
    double area = std::numbers::pi * radius * radius;

    double dx = (GD::WAVE_SPEED_MAX * dt) / GD::CFL;
    size_t N = std::ceil(length / dx);
    double dx_real = length / N;

    std::vector<Cell> cells;
    cells.reserve(N);
    for (size_t i = 0; i < N; ++i) {
        cells.emplace_back(
           GD::RHO_AMBIENT,             // rho
           0.0,                         // (rho * u), u = 0
           GD::P_ATM / (GD::GAMMA - 1)  // (p / (gamma - 1) + 0.5 * rho * u^2), u = 0
        );
    }

    std::vector<Flux> fluxes;
    fluxes.reserve(N + 1);
    for (size_t i = 0; i < (N + 1); ++i) {
        fluxes.emplace_back(
            0.0,        // Поток массы (rho * u)
            GD::P_ATM,  // Поток импульса (rho * u^2 + p)
            0.0         // Поток энергии (u * (E + p))
        );
    }

    return Pipe(
        area,
        dx_real,
        std::move(cells),
        std::move(fluxes)
    );
}
