#pragma once
#include <nlohmann/json_fwd.hpp>
#include <memory>

class Cylinder;

class CylinderBuilder {
public:
    static std::unique_ptr<Cylinder> build(const nlohmann::json& config, double offset = 0.0);
};
