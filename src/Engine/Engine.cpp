// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Engine.hpp"
#include <utility>

Engine::Engine(
    std::unique_ptr<Mechanics> mechanics,
    std::unique_ptr<GasDynamics> gasDynamics
):
    mechanics_(std::move(mechanics)),
    gasDynamics_(std::move(gasDynamics)) {}

void Engine::setOmega(double omega) {
    mechanics_->setOmega(omega);
}

void Engine::step(double dt) {
    gasDynamics_->step(dt);
    mechanics_->step(dt);
}
