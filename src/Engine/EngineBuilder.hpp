#pragma once
#include <nlohmann/json_fwd.hpp>

class Cylinder;
class CylinderBuilder;
class Engine;

class EngineBuilder {
public:
    static Engine build(const nlohmann::json& config);
};
