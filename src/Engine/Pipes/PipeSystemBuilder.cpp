#include "PipeSystemBuilder.hpp"
#include "PipeBuilder.hpp"
#include "JunctionBuilder.hpp"
#include "PipeSystem.hpp"
#include "Pipe.hpp"
#include "Atmosphere.hpp"
#include "../../Interfaces/IJunction.hpp"
#include "../Cylinder/Cylinder.hpp"

#include <nlohmann/json.hpp>
#include <memory>
#include <vector>

using json = nlohmann::json;

std::unique_ptr<PipeSystem> PipeSystemBuilder::build(
    const json& config,
    const std::vector<std::unique_ptr<Cylinder>>& cylinders,
    const double dt
) {
    // 1. Владеющие контейнеры — сразу в куче
    auto atmosphere = std::make_unique<Atmosphere>();
    auto pipes = createPipes(config["nodes"]["pipes"], dt);

    // 2. Junction'ы строим ПОСЛЕ — адреса *atmosphere и *pipes[i] финальны
    auto junctions = createJunctions(
        config["junctions"], *atmosphere, pipes, cylinders);

    // 3. Move unique_ptr — сами объекты остаются на месте
    return std::make_unique<PipeSystem>(
        std::move(atmosphere),
        std::move(pipes),
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
