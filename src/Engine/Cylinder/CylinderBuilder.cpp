#include "CylinderBuilder.hpp"
#include "Head/HeadBuilder.hpp"
#include "Block/BlockBuilder.hpp"
#include "Cylinder.hpp"
#include <memory>
#include <utility>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

CylinderBuilder::CylinderBuilder():
    headBuilder(std::make_unique<HeadBuilder>()),
    blockBuilder(std::make_unique<BlockBuilder>()) {}

CylinderBuilder::~CylinderBuilder() = default;

Cylinder CylinderBuilder::build(const json& config) {
    return Cylinder(
        config["gasketHeight"].get<double>(),
        std::move(headBuilder->build(config["head"])),
        std::move(blockBuilder->build(config["block"]))
    );
}
