#include "Engine.hpp"
#include <utility>
#include <numbers>
#include <cmath>
// #include <omp.h>

#include <iostream>

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
    angle_ += flywheel_->getOmega() * dt;
    angle_ = fmod(angle_, 4.0 * std::numbers::pi);
    if (angle_ < 0.0) angle_ += 4.0 * std::numbers::pi;
std::cout << "angle: " << angle_ / std::numbers::pi * 180 << std::endl;
    pipeSystem_->step(dt);

    double torque = 0.0;
    // #pragma omp parallel for
    // for (auto& cylinder : cylinders_) {
    for (size_t id = 0; id < cylinders_.size(); ++id) {
        cylinders_[id]->setKinematics(angle_, flywheel_->getOmega());
        cylinders_[id]->step(dt);

        torque += cylinders_[id]->calculateTorque();
    }

    // flywheel_->applyTorque(torque, dt);
    std::cout << "rpm: " << flywheel_->getOmega() / std::numbers::pi * 30 << std::endl;
    std::cout << std::endl;
}
