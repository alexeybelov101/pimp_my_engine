#include "ValvetrainBuilder.hpp"
#include "Camshaft/Camshaft.hpp"
#include "Camshaft/CamshaftBuilder.hpp"
#include "Valvetrain.hpp"
#include "Valve.hpp"
#include <memory>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

ValvetrainBuilder::ValvetrainBuilder():
    camBuilder(std::make_unique<CamshaftBuilder>()) {}

ValvetrainBuilder::~ValvetrainBuilder() = default;

Valvetrain ValvetrainBuilder::build(const json& config) {
    Camshaft camshaft = camBuilder->build(config["camshaft"]);

    const int lobeCount = config["camshaft"]["lobes"]["count"];
    const int valveCount = config["valves"]["count"];
    const auto& valveProto = config["valves"]["prototype"];

    std::vector<Valvetrain::LobeGroup> lobeGroup;
    lobeGroup.reserve(lobeCount);

    for (int i = 0; i < lobeCount; ++i) {

        for (int j = 0; j < valveCount; ++j) {

        }
    }
}

