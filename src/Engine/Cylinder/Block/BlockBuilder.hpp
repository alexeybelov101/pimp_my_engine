#pragma once
#include <nlohmann/json_fwd.hpp>

class Piston;
class Conrod;
class Crankshaft;
class Block;

class BlockBuilder {
public:
    Block build(const nlohmann::json& config);
private:
    Piston createPiston(const nlohmann::json& config);
    Conrod createConrod(const nlohmann::json& config);
    Crankshaft createCrankshaft(const nlohmann::json& config);
};
