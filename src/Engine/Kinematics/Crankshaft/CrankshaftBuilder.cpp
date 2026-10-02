// SPDX-License-Identifier: AGPL-3.0-or-later
#include "CrankshaftBuilder.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::unique_ptr<Crankshaft> CrankshaftBuilder::build(const json& config, Flywheel& flywheel) {
    return std::make_unique<Crankshaft>(
        config["radius"].get<double>(),
        createPins(config["crankpins"]),
        flywheel
    );
}

std::vector<Crankshaft::Pin> CrankshaftBuilder::createPins(const json& config) {
    std::vector<Crankshaft::Pin> pins;
    pins.reserve(config.size());

    for (const auto& pinProto : config) {
        pins.emplace_back(
            pinProto["position"].get<double>()
        );
    }

    return pins;
}
