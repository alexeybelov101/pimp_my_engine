// SPDX-License-Identifier: AGPL-3.0-or-later
#include "EngineBuilder.hpp"
#include "Kinematics/KinematicsBuilder.hpp"
#include "PipeSystem/PipeSystemBuilder.hpp"
#include "Engine.hpp"

#include <numbers>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

constexpr double MM_TO_M = 1.0e-3;
constexpr double G_TO_KG = 1.0e-3;

Engine EngineBuilder::build(const json& config, double dt) {
    auto kinematics = KinematicsBuilder::build(config["kinematics"]);
    auto pipeSystem = PipeSystemBuilder::build(config["pipeSystem"], cylinders, dt);

    return Engine(
        std::move(kinematics),
        std::move(pipeSystem)
    );
}
