#include "Engine.hpp"
#include <utility>
#include <numbers>
#include <cmath>
// #include <omp.h>

#include <iostream>

Engine::Engine(std::vector<Cylinder>&& cylinders, Flywheel&& flywheel):
    cylinders_(std::move(cylinders)), flywheel_(flywheel) {}

void Engine::setOmega(double omega) {
    flywheel_.setOmega(omega);
}

void Engine::step(double dt) {
    angle_ += flywheel_.getOmega() * dt;
    angle_ = fmod(angle_, 2.0 * std::numbers::pi);
    if (angle_ < 0.0) angle_ += 2.0 * std::numbers::pi;

    double torque = 0.0;
    // #pragma omp parallel for
    for (auto& cylinder : cylinders_) {
    // for (size_t id = 0; id < cylinders_.size(); ++id) {
        cylinder.setKinematics(angle_, flywheel_.getOmega());
        cylinder.step(dt);

        torque += cylinder.calculateTorque();
    }

    flywheel_.applyTorque(torque, dt);
}
