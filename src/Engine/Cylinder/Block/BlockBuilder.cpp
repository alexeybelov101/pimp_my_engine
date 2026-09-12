#include "BlockBuilder.hpp"
#include "BottomEnd/Piston.hpp"
#include "BottomEnd/Conrod.hpp"
#include "BottomEnd/Crankshaft.hpp"
#include "Block.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

constexpr double MM_TO_M = 1.0e-3;
constexpr double MM3_TO_M3 = 1.0e-9;

Block BlockBuilder::build(const json& config) {
    return Block(
        config["height"].get<double>() * MM_TO_M,
        config["gasketHeight"].get<double>() * MM_TO_M,
        createPiston(config["piston"]),
        createConrod(config["conrod"]),
        createCrankshaft(config["crankshaft"])
    );
}

Piston BlockBuilder::createPiston(const json& config) {
    return Piston(
        config["diameter"].get<double>() / 2.0 * MM_TO_M,
        config["compressionHeight"].get<double>() * MM_TO_M,
        config["deckVolume"].get<double>() * MM3_TO_M3
    );
}

Conrod BlockBuilder::createConrod(const json& config) {
    return Conrod(
        config["length"].get<double>() * MM_TO_M
    );
}

Crankshaft BlockBuilder::createCrankshaft(const json& config) {
    return Crankshaft(
        config["stroke"].get<double>() / 2.0 * MM_TO_M
    );
}
