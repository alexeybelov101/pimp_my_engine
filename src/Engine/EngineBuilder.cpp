#include "EngineBuilder.hpp"
#include "Cylinder/CylinderBuilder.hpp"
#include "Flywheel.hpp"
#include "Engine.hpp"
#include <utility>
#include <numbers>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

constexpr double MM_TO_M = 1.0e-3;
constexpr double G_TO_KG = 1.0e-3;

Engine EngineBuilder::build(const json& config) {
    std::vector<Cylinder> cylinders;

    size_t cylinderCount = config["cylinder"]["count"].get<size_t>();
    cylinders.reserve(cylinderCount);

    double offsetStep = 4.0 * std::numbers::pi / cylinderCount;
    for (size_t i = 0; i < cylinderCount; ++i) {
        cylinders.emplace_back(
            CylinderBuilder::build(config["cylinder"]["prototype"], offsetStep * i)
        );
    }

    return Engine(std::move(cylinders), createFlywheel(config["flywheel"]));
}

Flywheel EngineBuilder::createFlywheel(const json& config) {
    return Flywheel(
        config["mass"].get<double>() * G_TO_KG,
        config["radius"].get<double>() * MM_TO_M
    );
}
