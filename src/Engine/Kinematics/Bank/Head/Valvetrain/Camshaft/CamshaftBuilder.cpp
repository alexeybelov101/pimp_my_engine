// SPDX-License-Identifier: AGPL-3.0-or-later
#include "CamshaftBuilder.hpp"
#include "Camshaft.hpp"
#include <nlohmann/json.hpp>
#include <numbers>

constexpr double DEG_TO_RAD = std::numbers::pi / 180.0;
constexpr double MM_TO_M = 1.0e-3;

using json = nlohmann::json;

std::unique_ptr<Camshaft> CamshaftBuilder::build(const json& config) {
    return make_unique<Camshaft>(
        createLobes(config["lobes"])
    );
}

std::vector<Camshaft::Lobe> CamshaftBuilder::createLobes(const json& config) {
    std::vector<Camshaft::Lobe> lobes;
    lobes.reserve(config.size());

    for (const auto& lobeProto : config) {
        lobes.emplace_back(
            lobeProto["offset"].get<double>() / 2.0 * DEG_TO_RAD,
            lobeProto["maxLift"].get<double>() * MM_TO_M,
            lobeProto["duration"].get<double>() / 2.0 * DEG_TO_RAD
        );
    }

    return lobes;
}
