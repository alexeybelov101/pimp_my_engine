#include "PipeBuilder.hpp"
#include "Pipe.hpp"
#include "../../../Structs/Cell.hpp"
#include "../../../Structs/Flux.hpp"
#include "../../../Constants/GasDynamics.hpp"

#include <nlohmann/json.hpp>
#include <memory>
#include <numbers>
#include <cmath>
#include <vector>

namespace GD = GasDynamics;
using json = nlohmann::json;

constexpr double MM_TO_M = 1.0e-3;

std::unique_ptr<Pipe> PipeBuilder::build(const json& config, double dt) {
    const double length = config["length"].get<double>() * MM_TO_M;
    const double radius = config["radius"].get<double>() * MM_TO_M;
    const double area   = std::numbers::pi * radius * radius;

    const double dx = (GD::WAVE_SPEED_MAX * dt) / GD::CFL;
    const size_t N  = static_cast<size_t>(std::ceil(length / dx));
    const double dx_real = length / N;

    std::vector<Cell> cells;
    cells.reserve(N);
    for (size_t i = 0; i < N; ++i) {
        cells.emplace_back(
            GD::RHO_AMBIENT,
            0.0,
            GD::P_ATM / (GD::GAMMA - 1.0)
        );
    }

    std::vector<Flux> fluxes;
    fluxes.reserve(N + 1);
    for (size_t i = 0; i < N + 1; ++i) {
        fluxes.emplace_back(0.0, GD::P_ATM * area, 0.0);
    }

    // make_unique требует публичный конструктор Pipe(...)
    return std::make_unique<Pipe>(
        area,
        dx_real,
        std::move(cells),
        std::move(fluxes)
    );
}
