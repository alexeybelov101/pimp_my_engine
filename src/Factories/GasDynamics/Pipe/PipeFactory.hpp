// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Engine/GasDynamics/Pipe/Pipe.hpp"
#include "Structs/Cell.hpp"
#include "Structs/Flux.hpp"
#include "Constants/GasConstants.hpp"
#include "Utility/MeasureConverters.hpp"
#include <nlohmann/json.hpp>
#include <memory>
#include <numbers>
#include <cmath>
#include <vector>
#include <memory>

namespace MC = MeasureConverters;
namespace GC = GasConstants;
using json = nlohmann::json;

class Pipe;

class PipeFactory {
public:
    static std::unique_ptr<Pipe> build(const json& config, double dt) {
        const double length = MC::mmToM(config["length"].get<double>());
        const double radius = MC::mmToM(config["radius"].get<double>());
        const double area   = std::numbers::pi * radius * radius;

        const double dx = (GC::WAVE_SPEED_MAX * dt) / GC::CFL;
        const size_t N  = static_cast<size_t>(std::ceil(length / dx));
        const double dx_real = length / N;

        std::vector<Cell> cells;
        cells.reserve(N);
        for (size_t i = 0; i < N; ++i) {
            cells.emplace_back(
                GC::RHO_AMBIENT,
                0.0,
                GC::P_ATM / (GC::GAMMA - 1.0)
            );
        }

        std::vector<Flux> fluxes;
        fluxes.reserve(N + 1);
        for (size_t i = 0; i < N + 1; ++i) {
            fluxes.emplace_back(0.0, GC::P_ATM * area, 0.0);
        }

        // make_unique требует публичный конструктор Pipe(...)
        return std::make_unique<Pipe>(
            area,
            dx_real,
            std::move(cells),
            std::move(fluxes)
        );
    }
};
