// SPDX-License-Identifier: AGPL-3.0-or-later
#include "CrankshaftBuilder.hpp"
#include <nlohmann/json.hpp>
#include <numbers>

using json = nlohmann::json;

constexpr double MM_TO_M = 1.0e-3;
constexpr double DEG_TO_RAD = std::numbers::pi / 180.0;

std::unique_ptr<Crankshaft> CrankshaftBuilder::build(const json& config, Flywheel& flywheel) {
    return std::make_unique<Crankshaft>(
        config["radius"].get<double>() * MM_TO_M,
        createPins(config["crankpins"]),
        flywheel
    );
}

std::vector<Crankshaft::Pin> CrankshaftBuilder::createPins(const json& config) {
    std::vector<Crankshaft::Pin> pins;
    pins.reserve(config.size());

    for (const auto& pinProto : config) {
        pins.emplace_back(
            pinProto["offset"].get<double>() * DEG_TO_RAD
        );
    }

    return pins;
}
