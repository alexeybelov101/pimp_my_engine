// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Flywheel/FlywheelFactory.hpp"
#include "Crankshaft/CrankshaftFactory.hpp"
#include "Bank/BankFactory.hpp"
#include "Drive/DriveFactory.hpp"
#include "Engine/Mechanics/Crankshaft/Crankshaft.hpp"
#include "Engine/Mechanics/Bank/Head/Valvetrain/Valvetrain.hpp"
#include "Engine/Mechanics/Bank/Head/Head.hpp"
#include "Engine/Mechanics/Bank/Block/Block.hpp"
#include "Engine/Mechanics/Bank/Bank.hpp"
#include "Engine/Mechanics/Drive/Drive.hpp"
#include "Engine/Mechanics/Mechanics.hpp"
#include <nlohmann/json.hpp>
#include <memory>
#include <vector>

using json = nlohmann::json;

class MechanicsFactory {
public:
    struct MechanicsFactoryResult {
        std::unique_ptr<Mechanics> mechanics;
        std::vector<Head::Headlet*> all_headlets;
        std::vector<Block::Blocklet*> all_blocklets;
    };
    static MechanicsFactoryResult build(
        const json& config
    ) {
        auto flywheel = FlywheelFactory::build(config.at("flywheel"));
        auto [crankshaft, pins] = CrankshaftFactory::build(config.at("crankshaft"), flywheel.get());

        std::vector<std::unique_ptr<Bank>> banks;
        banks.reserve(config.at("banks").size());

        std::vector<Block::Blocklet*> all_blocklets;
        std::vector<Head::Headlet*> all_headlets;
        std::vector<Valvetrain*> valvetrains;

        for (auto& bankProto : config.at("banks")) {
            auto [bank, headlets, blocklets, valvetrain] = BankFactory::build(bankProto, pins);

            banks.emplace_back(std::move(bank));

            all_blocklets.insert(all_blocklets.end(), blocklets.begin(), blocklets.end());
            all_headlets.insert(all_headlets.end(), headlets.begin(), headlets.end());
            valvetrains.push_back(valvetrain);
        }

        auto drive = DriveFactory::build(crankshaft.get(), valvetrains);

        return {
            std::make_unique<Mechanics>(
                std::move(flywheel),
                std::move(crankshaft),
                std::move(banks),
                std::move(drive)
            ),
            all_headlets,
            all_blocklets
        };
    }
};
