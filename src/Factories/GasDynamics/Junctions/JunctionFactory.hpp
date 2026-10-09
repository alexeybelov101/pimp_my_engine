// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Engine/GasDynamics/Junctions/Junction2.hpp"
#include "Engine/GasDynamics/Junctions/Junction3.hpp"
#include "Engine/GasDynamics/Atmosphere/Atmosphere.hpp"
#include "Engine/GasDynamics/Pipe/Pipe.hpp"
#include "Engine/GasDynamics/Cylinder/Cylinder.hpp"
#include "Interfaces/IBoundary.hpp"
#include "Interfaces/IJunction.hpp"

#include <nlohmann/json.hpp>
#include <memory>
#include <vector>
#include <functional>

using json = nlohmann::json;

class JunctionFactory {
public:
    static std::unique_ptr<IJunction> build(
        const json& config,
        const Atmosphere& atmosphere,
        const std::vector<std::unique_ptr<Pipe>>& pipes,
        const std::vector<std::unique_ptr<Cylinder>>& cylinders)
    {
        auto boundaries = getBoundaries(config, atmosphere, pipes, cylinders);

        if (boundaries.size() == 2) {
            return std::make_unique<Junction2>(boundaries[0], boundaries[1]);
        }
        return std::make_unique<Junction3>(std::move(boundaries));
    }

private:
    static std::vector<std::reference_wrapper<const IBoundary>> getBoundaries(
        const json& config,
        const Atmosphere& atmosphere,
        const std::vector<std::unique_ptr<Pipe>>& pipes,
        const std::vector<std::unique_ptr<Cylinder>>& cylinders)
    {
        std::vector<std::reference_wrapper<const IBoundary>> boundaries;

        for (auto& [name, side] : config.items()) {
            const bool isLeft = (name == "left");
            for (auto& [key, value] : side.items()) {
                if (key == "atmosphere") {
                    boundaries.push_back(atmosphere.getBoundary(!isLeft));
                } else if (key == "pipes") {
                    for (auto& id : value) {
                        boundaries.push_back(pipes[id]->getBoundary(!isLeft));
                    }
                } else if (key == "cylinders") {
                    for (auto& id : value) {
                        boundaries.push_back(cylinders[id]->getBoundary(!isLeft));
                    }
                }
            }
        }

        return boundaries;
    }

};
