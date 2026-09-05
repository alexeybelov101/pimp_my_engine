#pragma once
#include <nlohmann/json_fwd.hpp>

class Cylinder;
class CylinderBuilder;
class Flywheel;
class Engine;

class EngineBuilder {
public:
    static Engine build(const nlohmann::json& config);
private:
    static Flywheel createFlywheel(const nlohmann::json& config);
};
