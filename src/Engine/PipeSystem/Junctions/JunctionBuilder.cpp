#include "JunctionBuilder.hpp"
#include "Junction2.hpp"
#include "Junction3.hpp"
#include "Engine/PipeSystem/Atmosphere/Atmosphere.hpp"
#include "Engine/PipeSystem/Pipe/Pipe.hpp"
#include "Engine/Cylinder/Cylinder.hpp"
#include "Interfaces/IBoundary.hpp"
#include "Interfaces/IJunction.hpp"

#include <nlohmann/json.hpp>
#include <memory>
#include <vector>
#include <functional>

using json = nlohmann::json;

std::unique_ptr<IJunction> JunctionBuilder::build(
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

std::vector<std::reference_wrapper<const IBoundary>> JunctionBuilder::getBoundaries(
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
