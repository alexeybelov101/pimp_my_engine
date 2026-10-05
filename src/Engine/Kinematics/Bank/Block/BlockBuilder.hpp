// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Piston.hpp"
#include "Conrod.hpp"
#include "Engine/Kinematics/Crankshaft/Crankshaft.hpp"
#include "Block.hpp"
#include <memory>
#include <vector>
#include <nlohmann/json_fwd.hpp>

class BlockBuilder {
public:
    static std::unique_ptr<Block> build(
        const nlohmann::json& config,
        Crankshaft* crankshaft
    );
private:
    static std::vector<std::unique_ptr<Piston>> createPistons(const nlohmann::json& config);
    static std::vector<std::unique_ptr<Conrod>> createConrods(const nlohmann::json& config);
    static std::vector<Block::Blocklet> createBlocklets(
        const nlohmann::json& config,
        std::vector<std::unique_ptr<Piston>>& pistons,
        std::vector<std::unique_ptr<Conrod>>& conrods,
        Crankshaft* crankshaft
    );
};
