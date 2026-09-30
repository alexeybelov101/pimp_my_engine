// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Engine.hpp"
#include <utility>
#include <numbers>
#include <cmath>
// #include <omp.h>

Engine::Engine(
    std::vector<std::unique_ptr<Cylinder>> cylinders,
    std::unique_ptr<Flywheel> flywheel,
    std::unique_ptr<PipeSystem> pipeSystem
):
    cylinders_(std::move(cylinders)),
    flywheel_(std::move(flywheel)),
    pipeSystem_(std::move(pipeSystem)) {}

void Engine::setOmega(double omega) {
    flywheel_->setOmega(omega);
}

void Engine::step(double dt) {
    pipeSystem_->step(dt);

    double torque = 0.0;
    // #pragma omp parallel for
    // for (auto& cylinder : cylinders_) {
    for (size_t id = 0; id < cylinders_.size(); ++id) {
        cylinders_[id]->setKinematics(angle_, flywheel_->getOmega());
        cylinders_[id]->step(dt);

        torque += cylinders_[id]->calculateTorque();
    }

    flywheel_->applyTorque(torque, dt);
}
