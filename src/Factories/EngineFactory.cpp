// SPDX-License-Identifier: AGPL-3.0-or-later
#include "EngineFactory.hpp"
#include "Mechanics/MechanicsFactory.hpp"
#include "Mechanics/Flywheel/FlywheelFactory.hpp"
#include "Mechanics/Crankshaft/CrankshaftFactory.hpp"
#include "Mechanics/Bank/BankFactory.hpp"
#include "GasDynamics/GasDynamicsFactory.hpp"
#include "Engine/Engine.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Engine EngineFactory::build(const json& config, double dt) {
    auto [mechanics, all_headlets, all_blocklets] = MechanicsFactory::build(config.at("mechanics"));
    auto gasDynamics = GasDynamicsFactory::build(config.at("gasDynamics"), all_headlets, all_blocklets, dt);

    return Engine(
        std::move(mechanics),
        std::move(gasDynamics)
    );
}
