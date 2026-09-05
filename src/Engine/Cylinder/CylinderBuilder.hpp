#pragma once
#include <nlohmann/json_fwd.hpp>

class Cylinder;

class CylinderBuilder {
public:
    static Cylinder build(const nlohmann::json& config);
    static Cylinder build(const nlohmann::json& config, double offset);
};
