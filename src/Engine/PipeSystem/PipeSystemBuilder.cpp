// SPDX-License-Identifier: AGPL-3.0-or-later
#include "PipeSystemBuilder.hpp"
#include "Engine/Kinematics/Kinematics.hpp"
#include "Pipe/PipeBuilder.hpp"
#include "Junctions/JunctionBuilder.hpp"
#include "PipeSystem.hpp"
#include "Pipe/Pipe.hpp"
#include "Atmosphere/Atmosphere.hpp"
#include "Interfaces/IJunction.hpp"
#include "Cylinder/Cylinder.hpp"

#include <nlohmann/json.hpp>
#include <memory>
#include <vector>

using json = nlohmann::json;

std::unique_ptr<PipeSystem> PipeSystemBuilder::build(
    const json& config,
    Kinematics* kinematics,
    const double dt
) {
    auto atmosphere = std::make_unique<Atmosphere>();
    auto pipes = createPipes(config["pipes"], dt);
    auto cylinders = createCylinders(config["cylinders"], kinematics);

    auto junctions = createJunctions(
        config["junctions"],
        *atmosphere,
        pipes,
        cylinders
    );

    return std::make_unique<PipeSystem>(
        std::move(atmosphere),
        std::move(pipes),
        std::move(cylinders),
        std::move(junctions)
    );
}

std::vector<std::unique_ptr<Pipe>> PipeSystemBuilder::createPipes(const json& config, double dt) {
    std::vector<std::unique_ptr<Pipe>> pipes;
    pipes.reserve(config.size());

    for (auto& pipeProto : config) {
        pipes.emplace_back(PipeBuilder::build(pipeProto, dt));
    }

    return pipes;
}

std::vector<std::unique_ptr<IJunction>> PipeSystemBuilder::createJunctions(
    const json& config,
    const Atmosphere& atmosphere,
    const std::vector<std::unique_ptr<Pipe>>& pipes,
    const std::vector<std::unique_ptr<Cylinder>>& cylinders)
{
    std::vector<std::unique_ptr<IJunction>> junctions;
    junctions.reserve(config.size());

    for (auto& junctionProto : config) {
        junctions.emplace_back(
            JunctionBuilder::build(junctionProto, atmosphere, pipes, cylinders)
        );
    }

    return junctions;
}

std::vector<std::unique_ptr<Cylinder>> PipeSystemBuilder::createCylinders(const json& config, Kinematics* kinematics) {
    std::vector<std::unique_ptr<Cylinder>> cylinders;
    cylinders.reserve(config.size());

    auto banks = kinematics->getBanks();
    std::vector<Head::Headlet*> headlets;
    std::vector<Block::Blocklet*> blocklets;
    for (auto& bank : banks) {
        auto hl = bank->getHeadlets();
        auto bl = bank->getBlocklets();
        headlets.insert(headlets.end(), hl.begin(), hl.end());
        blocklets.insert(blocklets.end(), bl.begin(), bl.end());
    }

    for (auto& cylinderProto : config) {
        cylinders.emplace_back(
            std::make_unique<Cylinder>(
                headlets[cylinderProto["headlet"].get<size_t>()],
                blocklets[cylinderProto["blocklet"].get<size_t>()]
            )
        );
    }

    return cylinders;
}
