// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Engine/Mechanics/Bank/Block/Piston.hpp"
#include "Engine/Mechanics/Bank/Block/Conrod.hpp"
#include "Engine/Mechanics/Crankshaft/Crankshaft.hpp"
#include "Engine/Mechanics/Bank/Block/Block.hpp"
#include "Utility/MeasureConverters.hpp"
#include "Templates/FactoryResult.hpp"
#include <nlohmann/json.hpp>
#include <memory>
#include <vector>

namespace MC = MeasureConverters;
using json = nlohmann::json;

class BlockFactory {
public:
    static FactoryResult<Block, Block::Blocklet> build(
        const json& config,
        std::vector<Crankshaft::Pin*> pins
    ) {
        auto pistons = createPistons(config["pistons"]);
        auto conrods = createConrods(config["conrods"]);
        auto blocklets = createBlocklets(config["blocklets"], pistons, conrods, pins);

        std::vector<Block::Blocklet*> blocklets_ptr;
        blocklets_ptr.reserve(blocklets.size());
        for (const auto& blocklet : blocklets) {
            blocklets_ptr.emplace_back(blocklet.get());
        }

        return FactoryResult<Block, Block::Blocklet>{
            std::make_unique<Block>(
                MC::mmToM(config["height"].get<double>()),
                MC::mmToM(config["gasketHeight"].get<double>()),
                std::move(pistons),
                std::move(conrods),
                std::move(blocklets)
            ),
            std::move(blocklets_ptr)
        };

;
    }
private:
    static std::vector<std::unique_ptr<Piston>> createPistons(const nlohmann::json& config) {
        std::vector<std::unique_ptr<Piston>> pistons;
        pistons.reserve(config.size());

        for (const auto& pistonProto : config) {
            pistons.emplace_back(
                std::make_unique<Piston>(
                    MC::mmToM(pistonProto["diameter"].get<double>() / 2.0),
                    MC::mmToM(pistonProto["compressionHeight"].get<double>()),
                    MC::mm3ToM3(pistonProto["deckVolume"].get<double>())
                )
            );
        }

        return pistons;
    }

    static std::vector<std::unique_ptr<Conrod>> createConrods(const nlohmann::json& config) {
        std::vector<std::unique_ptr<Conrod>> conrods;
        conrods.reserve(config.size());

        for (const auto& conrodProto : config) {
            conrods.emplace_back(
                std::make_unique<Conrod>(
                    MC::mmToM(conrodProto["length"].get<double>())
                )
            );
        }

        return conrods;
    }

    static std::vector<std::unique_ptr<Block::Blocklet>> createBlocklets(
        const nlohmann::json& config,
        std::vector<std::unique_ptr<Piston>>& pistons,
        std::vector<std::unique_ptr<Conrod>>& conrods,
        std::vector<Crankshaft::Pin*> pins
    ) {

        std::vector<std::unique_ptr<Block::Blocklet>> blocklets;
        blocklets.reserve(config.size());
        for (size_t i = 0; i < config.size(); ++i) {
            const auto& blockletProto = config[i];

            blocklets.emplace_back(
                std::make_unique<Block::Blocklet>(
                    pistons[blockletProto["piston"].get<size_t>()].get(),
                    conrods[blockletProto["conrod"].get<size_t>()].get(),
                    pins[blockletProto["pin"].get<size_t>()]
                )
            );
        }

        return blocklets;
    };
};
