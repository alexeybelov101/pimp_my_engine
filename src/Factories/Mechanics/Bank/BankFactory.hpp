// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Factories/Mechanics/Bank/Head/HeadFactory.hpp"
#include "Factories/Mechanics/Bank/Block/BlockFactory.hpp"
#include "Engine/Mechanics/Bank/Head/Valvetrain/Valvetrain.hpp"
#include "Engine/Mechanics/Bank/Head/Head.hpp"
#include "Engine/Mechanics/Bank/Block/Block.hpp"
#include "Engine/Mechanics/Bank/Bank.hpp"
#include "Utility/MeasureConverters.hpp"
#include <nlohmann/json.hpp>
#include <memory>

namespace MC = MeasureConverters;
using json = nlohmann::json;

class BankFactory {
public:
    struct BankFactoryResult {
        std::unique_ptr<Bank> bank;
        std::vector<Head::Headlet*> headlets;
        std::vector<Block::Blocklet*> blocklets;
        Valvetrain* valvetrain;
    };

    static BankFactoryResult build(
        const json& config,
        std::vector<Crankshaft::Pin*> pins
    ) {
        auto [block, blocklets] = BlockFactory::build(config.at("block"), pins);
        auto [head, headlets, valvetrain] = HeadFactory::build(config.at("head"));

        return {
            std::make_unique<Bank>(
                MC::degToRad(config.at("offset").get<double>()),
                std::move(head),
                std::move(block)
            ),
            headlets,
            blocklets,
            valvetrain
        };
    }
};
