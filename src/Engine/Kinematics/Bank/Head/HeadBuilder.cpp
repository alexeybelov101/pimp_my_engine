// SPDX-License-Identifier: AGPL-3.0-or-later
#include "HeadBuilder.hpp"
#include "Valvetrain/ValvetrainBuilder.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

constexpr double MM3_TO_M3 = 1.0e-9;

std::unique_ptr<Head> HeadBuilder::build(const json& config) {
    auto intakeValvetrain = ValvetrainBuilder::build(config["intakeValvetrain"]);
    auto exhaustValvetrain = ValvetrainBuilder::build(config["exhaustValvetrain"]);
    auto headlets = createHeadlets(
        config["headlets"],
        intakeValvetrain.get(),
        exhaustValvetrain.get()
    );

    return std::make_unique<Head>(
        config["chamberVolume"].get<double>() * MM3_TO_M3,
        std::move(intakeValvetrain),
        std::move(exhaustValvetrain),
        std::move(headlets)
    );
}

std::vector<Head::Headlet> HeadBuilder::createHeadlets(
    const json& config,
    Valvetrain* intakeValvetrain,
    Valvetrain* exhaustValvetrain
) {
    auto intakeLinks = intakeValvetrain->getLinks();
    auto exhaustLinks = exhaustValvetrain->getLinks();

    std::vector<Head::Headlet> headlets;
    headlets.reserve(config.size());

    for (const auto& headletProto : config) {
        headlets.emplace_back(
            intakeLinks[headletProto["intakeLink"].get<size_t>()],
            exhaustLinks[headletProto["exhaustLink"].get<size_t>()]
        );
    }
    return headlets;
}
