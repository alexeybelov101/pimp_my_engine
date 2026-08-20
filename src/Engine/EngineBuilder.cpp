#include "EngineBuilder.hpp"
#include "Cylinder/Cylinder.hpp"
#include "Cylinder/CylinderBuilder.hpp"
#include "Engine.hpp"
#include <utility>
#include <nlohmann/json.hpp>

#define _USE_MATH_DEFINES
#include <cmath>
#define DEG_TO_RAD (M_PI / 180.0)

using json = nlohmann::json;

EngineBuilder::EngineBuilder():
    cylinderBuilder(std::make_unique<CylinderBuilder>()) {}

EngineBuilder::~EngineBuilder() = default;

Engine EngineBuilder::build(const json& config) {
    std::vector<Engine::CylPos> cylPos;

    size_t cylinderCount = config["cylinder"]["count"].get<size_t>();
    cylPos.reserve(cylinderCount);

    double positionStep = 2 * M_PI / cylinderCount;
    for (size_t i = 0; i < cylinderCount; ++i) {
        cylPos.emplace_back(
            std::move(
                cylinderBuilder->build(config["prototype"])
            ),
            positionStep * i
        );
    }

    return Engine(std::move(cylPos));
}
