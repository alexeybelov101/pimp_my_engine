// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Engine.hpp"
#include <utility>

Engine::Engine(
    std::unique_ptr<Kinematics> kinematics,
    std::unique_ptr<PipeSystem> pipeSystem
):
    kinematics_(std::move(kinematics)),
    pipeSystem_(std::move(pipeSystem)) {}

void Engine::setOmega(double omega) {
    kinematics_->setOmega(omega);
}

void Engine::step(double dt) {
    pipeSystem_->step(dt);
    kinematics_->step(dt);
}
