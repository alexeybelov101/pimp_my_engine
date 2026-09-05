#include "HeadBuilder.hpp"
#include "Valvetrain/ValvetrainBuilder.hpp"
#include "Head.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

constexpr double MM3_TO_M3 = 1.0e-9;

Head HeadBuilder::build(const json& config) {
    return Head(
        config["chamberVolume"].get<double>() * MM3_TO_M3,
        ValvetrainBuilder::build(config["intakeValvetrain"]),
        ValvetrainBuilder::build(config["exhaustValvetrain"])
    );
}
