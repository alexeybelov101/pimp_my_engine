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
    camshaftBuilder(std::make_unique<CamshaftBuilder>()) {}

ValvetrainBuilder::~ValvetrainBuilder() = default;

Valvetrain ValvetrainBuilder::build(const json& config) {
    Camshaft camshaft = camshaftBuilder->build(config["camshaft"]);
    std::vector<std::vector<Valve>> lobeValves = createLobeValves(
        config["valve"],
        config["camshaft"]["lobe"]["count"].get<size_t>()
    );

    return Valvetrain(std::move(camshaft), std::move(lobeValves));
}

std::vector<std::vector<Valve>> ValvetrainBuilder::createLobeValves(const json& config, size_t lobeCount) {
    const size_t valvesPerLobe = config["count"].get<size_t>();
    const auto& valveProto = config["prototype"];

    std::vector<Valve> templateValves;
    templateValves.reserve(valvesPerLobe);

    for (size_t valveId = 0; valveId < valvesPerLobe; ++valveId) {
        templateValves.emplace_back(
            valveProto["headDiameter"].get<double>(),
            valveProto["seatAngle"].get<double>()
        );
    }

    std::vector<std::vector<Valve>> lobeValves;
    lobeValves.reserve(lobeCount);

    for (size_t lobeId = 0; lobeId < lobeCount; ++lobeId) {
        lobeValves.push_back(templateValves);
    }

    return lobeValves;
}

