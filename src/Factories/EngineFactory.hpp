// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <nlohmann/json_fwd.hpp>

class Engine;

class EngineFactory {
public:
    static Engine build(const nlohmann::json& config, double dt);
};
