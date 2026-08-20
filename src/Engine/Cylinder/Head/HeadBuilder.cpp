#include "HeadBuilder.hpp"
#include "Valvetrain/ValvetrainBuilder.hpp"
#include "Head.hpp"
#include <utility>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

HeadBuilder::HeadBuilder():
    valvetrainBuilder(std::make_unique<ValvetrainBuilder>()) {}

HeadBuilder::~HeadBuilder() = default;

Head HeadBuilder::build(const json& config) {
    return Head(
        config["chamberVolume"].get<double>(),
        std::move(valvetrainBuilder->build(config["intakeValvetrain"])),
        std::move(valvetrainBuilder->build(config["exhaustValvetrain"]))
    );
}
