#include "BlockBuilder.hpp"
#include "BottomEnd/Piston.hpp"
#include "BottomEnd/Conrod.hpp"
#include "BottomEnd/Crankshaft.hpp"
#include "Block.hpp"
#include <utility>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Block BlockBuilder::build(const json& config) {
    return Block(
        config["height"].get<double>(),
        std::move(createPiston(config["piston"])),
        std::move(createConrod(config["conrod"])),
        std::move(createCrankshaft(config["crankshaft"]))
    );
}

Piston BlockBuilder::createPiston(const json& config) {
    return Piston(
        config["diameter"].get<double>(),
        config["compressionHeight"].get<double>(),
        config["deckVolume"].get<double>()
    );
}

Conrod BlockBuilder::createConrod(const json& config) {
    return Conrod(
        config["length"].get<double>()
    );
}

Crankshaft BlockBuilder::createCrankshaft(const json& config) {
    return Crankshaft(
        config["radius"].get<double>()
    );
}
