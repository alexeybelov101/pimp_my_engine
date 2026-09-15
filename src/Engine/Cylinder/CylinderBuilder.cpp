// SPDX-License-Identifier: AGPL-3.0-or-later
#include "CylinderBuilder.hpp"
#include "Head/HeadBuilder.hpp"
#include "Block/BlockBuilder.hpp"
#include "Cylinder.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::unique_ptr<Cylinder> CylinderBuilder::build(const json& config, double offset) {
    return std::make_unique<Cylinder>(
        HeadBuilder::build(config["head"]),
        BlockBuilder::build(config["block"]),
        offset
    );
}
