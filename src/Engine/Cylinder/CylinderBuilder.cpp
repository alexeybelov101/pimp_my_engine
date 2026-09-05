#include "CylinderBuilder.hpp"
#include "Head/HeadBuilder.hpp"
#include "Block/BlockBuilder.hpp"
#include "Cylinder.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Cylinder CylinderBuilder::build(const json& config) {
    return Cylinder(
        HeadBuilder::build(config["head"]),
        BlockBuilder::build(config["block"])
    );
}

Cylinder CylinderBuilder::build(const json& config, double offset) {
    return Cylinder(
        HeadBuilder::build(config["head"]),
        BlockBuilder::build(config["block"]),
        offset
    );
}
