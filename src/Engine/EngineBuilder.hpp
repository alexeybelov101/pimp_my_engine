// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <nlohmann/json_fwd.hpp>

class Kinematics;
class PipeSystem;
class Engine;

class EngineBuilder {
public:
    static Engine build(const nlohmann::json& config, double dt);
};
