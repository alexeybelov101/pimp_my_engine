// SPDX-License-Identifier: AGPL-3.0-or-later
#include "ValvetrainBuilder.hpp"
#include "Camshaft/CamshaftBuilder.hpp"
#include "Engine/Kinematics/Bank/Head/Valvetrain/Valve.hpp"
#include <nlohmann/json.hpp>
#include <memory>
#include <numbers>
#include <cmath>

constexpr double DEG_TO_RAD = std::numbers::pi / 180.0;
constexpr double MM_TO_M = 1.0e-3;

using json = nlohmann::json;

std::unique_ptr<Valvetrain> ValvetrainBuilder::build(const json& config) {
    auto camshaft = CamshaftBuilder::build(config["camshaft"]);
    auto valves = createValves(config["valves"]);
    auto links = createLinks(config["links"], camshaft.get(), &valves);

    return std::make_unique<Valvetrain>(
        std::move(camshaft),
        std::move(valves),
        std::move(links)
    );
}

std::vector<std::unique_ptr<Valve>> ValvetrainBuilder::createValves(const json& config) {
    std::vector<std::unique_ptr<Valve>> valves;
    valves.reserve(config.size());

    for (const auto& valveProto : config) {
        valves.emplace_back(
            std::make_unique<Valve>(
                valveProto["headDiameter"].get<double>() / 2.0 * MM_TO_M,
                std::sin(valveProto["seatAngle"].get<double>() * DEG_TO_RAD),
                std::cos(valveProto["seatAngle"].get<double>() * DEG_TO_RAD)
            )
        );
    }
    return valves;
}

std::vector<Valvetrain::Link> ValvetrainBuilder::createLinks(
    const json& config,
    Camshaft* camshaft,
    std::vector<std::unique_ptr<Valve>>* valves
) {
    auto lobes = camshaft->getLobes();
    std::vector<Valvetrain::Link> links;
    links.reserve(config.size());

    for (auto& linkProto : config) {
        std::vector<Camshaft::Lobe*> linkLobes;
        linkLobes.reserve(linkProto["lobes"].size());
        for (auto& lobeId : linkProto["lobes"]) {
            linkLobes.emplace_back(lobes[lobeId]);
        }

        std::vector<Valve*> linkValves;
        linkValves.reserve(linkProto["valves"].size());
        for (auto& valveId : linkProto["valves"]) {
            linkValves.emplace_back((*valves)[valveId].get());
        }

        links.emplace_back(
            std::move(linkLobes),
            std::move(linkValves)
        );
    }

    return links;
}
