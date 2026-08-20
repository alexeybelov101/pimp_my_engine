#include "ValvetrainBuilder.hpp"
#include "Camshaft/Camshaft.hpp"
#include "Camshaft/CamshaftBuilder.hpp"
#include "Valvetrain.hpp"
#include "Valve.hpp"
#include <memory>
#include <utility>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

ValvetrainBuilder::ValvetrainBuilder():
    camBuilder(std::make_unique<CamshaftBuilder>()) {}

ValvetrainBuilder::~ValvetrainBuilder() = default;

Valvetrain ValvetrainBuilder::build(const json& config) {
    Camshaft camshaft = camBuilder->build(config["camshaft"]);
    std::vector<std::vector<Valve>> lobeValves = createLobeValves(config["valve"], static_cast<size_t>(config["camshaft"]["lobe"]["count"]));

    return Valvetrain(std::move(camshaft), std::move(lobeValves));
}

std::vector<std::vector<Valve>> ValvetrainBuilder::createLobeValves(const json& config, size_t lobeCount) {
    const size_t valvesPerLobe = static_cast<size_t>(config["count"]);
    const auto& valveProto = config["prototype"];

    std::vector<Valve> templateValves;
    templateValves.reserve(valvesPerLobe);

    for (size_t valveId = 0; valveId < valvesPerLobe; ++valveId) {
        templateValves.emplace_back(valveProto["headDiameter"], valveProto["seatAngle"]);
    }

    std::vector<std::vector<Valve>> lobeValves;
    lobeValves.reserve(lobeCount);

    for (size_t lobeId = 0; lobeId < lobeCount; ++lobeId) {
        lobeValves.push_back(templateValves);
    }

    return lobeValves;
}

