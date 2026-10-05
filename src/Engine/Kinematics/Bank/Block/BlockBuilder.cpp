// SPDX-License-Identifier: AGPL-3.0-or-later
#include "BlockBuilder.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

constexpr double MM_TO_M = 1.0e-3;
constexpr double MM3_TO_M3 = 1.0e-9;

std::unique_ptr<Block> BlockBuilder::build(
    const json& config,
    Crankshaft* crankshaft
) {
    auto pistons = createPistons(config["pistons"]);
    auto conrods = createConrods(config["conrods"]);
    auto blocklets = createBlocklets(config["blocklets"], pistons, conrods, crankshaft);

    return std::make_unique<Block>(
        config["height"].get<double>() * MM_TO_M,
        config["gasketHeight"].get<double>() * MM_TO_M,
        std::move(pistons),
        std::move(conrods),
        std::move(blocklets)
    );
}

std::vector<std::unique_ptr<Piston>> BlockBuilder::createPistons(const nlohmann::json& config) {
    std::vector<std::unique_ptr<Piston>> pistons;
    pistons.reserve(config.size());

    for (const auto& pistonProto : config) {
        pistons.emplace_back(
            std::make_unique<Piston>(
                pistonProto["diameter"].get<double>() / 2.0 * MM_TO_M,
                pistonProto["compressionHeight"].get<double>() * MM_TO_M,
                pistonProto["deckVolume"].get<double>() * MM3_TO_M3
            )
        );
    }

    return pistons;
}

std::vector<std::unique_ptr<Conrod>> BlockBuilder::createConrods(const nlohmann::json& config) {
    std::vector<std::unique_ptr<Conrod>> conrods;
    conrods.reserve(config.size());

    for (const auto& conrodProto : config) {
        conrods.emplace_back(
            std::make_unique<Conrod>(
                conrodProto["length"].get<double>() * MM_TO_M
            )
        );
    }

    return conrods;
}

std::vector<Block::Blocklet> BlockBuilder::createBlocklets(
    const nlohmann::json& config,
    std::vector<std::unique_ptr<Piston>>& pistons,
    std::vector<std::unique_ptr<Conrod>>& conrods,
    Crankshaft* crankshaft
) {
    auto pins = crankshaft->getPins();

    std::vector<Block::Blocklet> blocklets;
    blocklets.reserve(config.size());
    for (size_t i = 0; i < config.size(); ++i) {
        const auto& blockletProto = config[i];

        blocklets.emplace_back(
            pistons[blockletProto["piston"].get<size_t>()].get(),
            conrods[blockletProto["conrod"].get<size_t>()].get(),
            pins[blockletProto["pin"].get<size_t>()]
        );
    }

    return blocklets;
};
