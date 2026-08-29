#include "EngineBuilder.hpp"
#include "Cylinder/CylinderBuilder.hpp"
#include "Engine.hpp"
#include <utility>
#include <numbers>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Engine EngineBuilder::build(const json& config) {
    std::vector<Engine::CylPos> cylPos;

    size_t cylinderCount = config["cylinder"]["count"].get<size_t>();
    cylPos.reserve(cylinderCount);

    double positionStep = 4.0 * std::numbers::pi / cylinderCount;
    for (size_t i = 0; i < cylinderCount; ++i) {
        cylPos.emplace_back(
            CylinderBuilder::build(config["cylinder"]["prototype"]),
            positionStep * i
        );
    }

    return Engine(std::move(cylPos));
}
