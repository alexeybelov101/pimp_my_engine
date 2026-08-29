#include "HeadBuilder.hpp"
#include "Valvetrain/ValvetrainBuilder.hpp"
#include "Head.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Head HeadBuilder::build(const json& config) {
    return Head(
        config["chamberVolume"].get<double>(),
        ValvetrainBuilder::build(config["intakeValvetrain"]),
        ValvetrainBuilder::build(config["exhaustValvetrain"])
    );
}
