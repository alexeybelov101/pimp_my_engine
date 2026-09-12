#include "EngineBuilder.hpp"
#include "Cylinder/CylinderBuilder.hpp"
#include "Flywheel.hpp"
#include "Pipes/Atmosphere.hpp"
#include "Pipes/PipeSystem.hpp"
#include "Pipes/PipeSystemBuilder.hpp"
#include "Engine.hpp"
#include <numbers>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

constexpr double MM_TO_M = 1.0e-3;
constexpr double G_TO_KG = 1.0e-3;

Engine EngineBuilder::build(const json& config, double dt) {
    auto cylinders = createCylinders(config);
    auto flywheel = createFlywheel(config["flywheel"]);
    auto pipeSystem = PipeSystemBuilder::build(config["pipeSystem"], cylinders, dt);

    return Engine(
        std::move(cylinders),
        std::move(flywheel),
        std::move(pipeSystem)
    );
}

std::unique_ptr<Flywheel> EngineBuilder::createFlywheel(const json& config) {
    return std::make_unique<Flywheel>(
        config["mass"].get<double>() * G_TO_KG,
        config["diameter"].get<double>() / 2.0 * MM_TO_M
    );
}

std::vector<std::unique_ptr<Cylinder>> EngineBuilder::createCylinders(const json& config) {
    size_t cylinderCount = config["cylinder"]["count"].get<size_t>();
    double offsetStep = 4.0 * std::numbers::pi / cylinderCount;

    std::vector<std::unique_ptr<Cylinder>> cylinders;
    cylinders.reserve(cylinderCount);

    for (size_t i = 0; i < cylinderCount; ++i) {
        cylinders.emplace_back(
            CylinderBuilder::build(config["cylinder"]["prototype"], offsetStep * i)
        );
    }

    return cylinders;
}
