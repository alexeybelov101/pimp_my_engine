#include "PipeSystemBuilder.hpp"
#include "Pipe.hpp"
#include "PipeSystem.hpp"
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// PipeSystem PipeSystemBuilder::build(const json& config) {
//     std::vector<Pipe> pipes = createPipes(config["pipes"]);
//
// }
/*
std::vector<Pipe> createPipes(const json& config) {
    std::vector<Pipe> pipes;
    pipes.reserve(config.size());

    for (auto& pipeProto : config) {
        pipes.emplace_back(
            pipeProto["length"],
            pipeProto["radius"]
        );
    }

    for (auto& pipeProto : config) {
        auto& pipe = pipes[pipeProto["id"]];
        for (auto& childId : pipeProto["children"]) {
            auto& child = pipes[childId];
            pipe.appendChild(&child);
            child.appendParent(&pipe);
        }
    }

    return pipes;
}*/

