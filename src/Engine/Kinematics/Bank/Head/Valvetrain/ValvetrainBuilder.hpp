// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Engine/Kinematics/Bank/Head/Valvetrain/Camshaft/Camshaft.hpp"
#include "Valve.hpp"
#include "Valvetrain.hpp"
#include <nlohmann/json_fwd.hpp>
#include <memory>

class Valve;
class Valvetrain;

class ValvetrainBuilder {
public:
    static std::unique_ptr<Valvetrain> build(const nlohmann::json& config);
private:
    static std::vector<std::unique_ptr<Valve>> createValves(const nlohmann::json& config);
    static std::vector<Valvetrain::Link> createLinks(
        const nlohmann::json& config,
        Camshaft* camshaft,
        std::vector<std::unique_ptr<Valve>>* valves
    );
};
