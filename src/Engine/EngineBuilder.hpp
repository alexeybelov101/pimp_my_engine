// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <nlohmann/json_fwd.hpp>
#include <memory>

class Cylinder;
class CylinderBuilder;
class Flywheel;
class PipeSystem;
class Engine;

class EngineBuilder {
public:
    static Engine build(const nlohmann::json& config, double dt);
private:
    static std::vector<std::unique_ptr<Cylinder>> createCylinders(const nlohmann::json& config);
    static std::unique_ptr<Flywheel> createFlywheel(const nlohmann::json& config);
};
