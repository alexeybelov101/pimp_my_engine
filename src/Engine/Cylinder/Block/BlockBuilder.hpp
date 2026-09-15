// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <nlohmann/json_fwd.hpp>

class Piston;
class Conrod;
class Crankshaft;
class Block;

class BlockBuilder {
public:
    static Block build(const nlohmann::json& config);
private:
    static Piston createPiston(const nlohmann::json& config);
    static Conrod createConrod(const nlohmann::json& config);
    static Crankshaft createCrankshaft(const nlohmann::json& config);
};
