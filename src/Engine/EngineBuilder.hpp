#pragma once
#include <memory>
#include <nlohmann/json_fwd.hpp>

class Cylinder;
class CylinderBuilder;
class Engine;

class EngineBuilder {
public:
    EngineBuilder();
    ~EngineBuilder();

    Engine build(const nlohmann::json& config);
private:
    std::unique_ptr<CylinderBuilder> cylinderBuilder;
};
