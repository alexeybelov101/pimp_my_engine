// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Engine/Mechanics/Flywheel/Flywheel.hpp"
#include "Utility/MeasureConverters.hpp"
#include <nlohmann/json.hpp>
#include <memory>

namespace MC = MeasureConverters;
using json = nlohmann::json;

class FlywheelFactory {
public:
    static std::unique_ptr<Flywheel> build(const json& config) {
        return std::make_unique<Flywheel>(
            MC::gToKg(config["mass"].get<double>()),
            MC::mmToM(config["diameter"].get<double>() * 0.5)
        );
    }
};
