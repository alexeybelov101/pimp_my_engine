// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Pipe/PipeFactory.hpp"
#include "Junctions/JunctionFactory.hpp"
#include "Engine/GasDynamics/GasDynamics.hpp"
#include "Engine/GasDynamics/Atmosphere/Atmosphere.hpp"
#include "Engine/GasDynamics/Pipe/Pipe.hpp"
#include "Engine/GasDynamics/Cylinder/Cylinder.hpp"
#include "Engine/Mechanics/Bank/Head/Head.hpp"
#include "Engine/Mechanics/Bank/Block/Block.hpp"
#include "Interfaces/IJunction.hpp"
#include <nlohmann/json.hpp>
#include <memory>
#include <vector>

using json = nlohmann::json;

class GasDynamicsFactory {
public:
    static std::unique_ptr<GasDynamics> build(
        const json& config,
        std::vector<Head::Headlet*> headlets,
        std::vector<Block::Blocklet*> blocklets,
        const double dt
    ) {
        auto atmosphere = std::make_unique<Atmosphere>();
        auto pipes = createPipes(config["pipes"], dt);
        auto cylinders = createCylinders(config["cylinders"], headlets, blocklets);

        auto junctions = createJunctions(
            config["junctions"],
            *atmosphere,
            pipes,
            cylinders
        );

        return std::make_unique<GasDynamics>(
            std::move(atmosphere),
            std::move(pipes),
            std::move(cylinders),
            std::move(junctions)
        );
    }

private:
    static std::vector<std::unique_ptr<Pipe>> createPipes(const json& config, double dt) {
        std::vector<std::unique_ptr<Pipe>> pipes;
        pipes.reserve(config.size());

        for (auto& pipeProto : config) {
            pipes.emplace_back(PipeFactory::build(pipeProto, dt));
        }

        return pipes;
    }

    static std::vector<std::unique_ptr<Cylinder>> createCylinders(
        const json& config,
        std::vector<Head::Headlet*> headlets,
        std::vector<Block::Blocklet*> blocklets
    ) {
        std::vector<std::unique_ptr<Cylinder>> cylinders;
        cylinders.reserve(config.size());

        for (auto& cylinderProto : config) {
            cylinders.emplace_back(
                std::make_unique<Cylinder>(
                    headlets[cylinderProto.at("headlet").get<size_t>()],
                    blocklets[cylinderProto.at("blocklet").get<size_t>()]
                )
            );
        }

        return cylinders;
    }

    static std::vector<std::unique_ptr<IJunction>> createJunctions(
        const json& config,
        const Atmosphere& atmosphere,
        const std::vector<std::unique_ptr<Pipe>>& pipes,
        const std::vector<std::unique_ptr<Cylinder>>& cylinders)
    {
        std::vector<std::unique_ptr<IJunction>> junctions;
        junctions.reserve(config.size());

        for (auto& junctionProto : config) {
            junctions.emplace_back(
                JunctionFactory::build(junctionProto, atmosphere, pipes, cylinders)
            );
        }

        return junctions;
    }
};
