// SPDX-License-Identifier: AGPL-3.0-or-later
#include "BankBuilder.hpp"
#include "Head/HeadBuilder.hpp"
#include "Block/BlockBuilder.hpp"
#include "Bank.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::unique_ptr<Bank> BankBuilder::build(const json& config, double offset) {
    return std::make_unique<Bank>(
        HeadBuilder::build(config["head"]),
        BlockBuilder::build(config["block"]),
        offset
    );
}
