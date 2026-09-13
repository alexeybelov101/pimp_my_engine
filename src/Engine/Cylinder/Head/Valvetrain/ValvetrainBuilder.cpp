#include "ValvetrainBuilder.hpp"
#include "Camshaft/CamshaftBuilder.hpp"
#include "Valvetrain.hpp"
#include "Valve.hpp"
#include <nlohmann/json.hpp>
#include <numbers>
#include <cmath>

constexpr double DEG_TO_RAD = std::numbers::pi / 180.0;
constexpr double MM_TO_M = 1.0e-3;

using json = nlohmann::json;

Valvetrain ValvetrainBuilder::build(const json& config) {
    return Valvetrain(
        CamshaftBuilder::build(config["camshaft"]),
        createLobeValves(
            config["valve"],
            config["camshaft"]["lobe"]["count"].get<size_t>()
        )
    );
}

std::vector<std::vector<Valve>> ValvetrainBuilder::createLobeValves(const json& config, size_t lobeCount) {
    const size_t valvesPerLobe = config["count"].get<size_t>();
    const auto& valveProto = config["prototype"];

    std::vector<Valve> templateValves;
    templateValves.reserve(valvesPerLobe);

    for (size_t valveId = 0; valveId < valvesPerLobe; ++valveId) {
        templateValves.emplace_back(
            valveProto["headDiameter"].get<double>() / 2.0 * MM_TO_M,
            std::sin(valveProto["seatAngle"].get<double>() * DEG_TO_RAD),
            std::cos(valveProto["seatAngle"].get<double>() * DEG_TO_RAD)
        );
    }

    std::vector<std::vector<Valve>> lobeValves;
    lobeValves.reserve(lobeCount);

    for (size_t lobeId = 0; lobeId < lobeCount; ++lobeId) {
        lobeValves.push_back(templateValves);
    }

    return lobeValves;
}
