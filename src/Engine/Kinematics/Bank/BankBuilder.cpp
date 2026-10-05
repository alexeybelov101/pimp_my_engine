// SPDX-License-Identifier: AGPL-3.0-or-later
#include "BankBuilder.hpp"
#include "Head/HeadBuilder.hpp"
#include "Engine/Kinematics/Crankshaft/Crankshaft.hpp"
#include "Block/BlockBuilder.hpp"
#include "Bank.hpp"
#include <nlohmann/json.hpp>
#include <numbers>

using json = nlohmann::json;

constexpr double DEG_TO_RAD = std::numbers::pi / 180.0;

std::vector<std::unique_ptr<Bank>> BankBuilder::build(const json& config, Crankshaft* crankshaft) {
    std::vector<std::unique_ptr<Bank>> banks;
    banks.reserve(config.size());

    for (const auto& bankProto : config) {
        banks.emplace_back(
            std::make_unique<Bank>(
                bankProto["offset"].get<double>() * DEG_TO_RAD,
                HeadBuilder::build(bankProto["head"]),
                BlockBuilder::build(bankProto["block"], crankshaft)
            )
        );
    }

    return banks;
}
