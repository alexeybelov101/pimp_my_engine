#include "Engine.hpp"
#include <utility>
#include <numbers>
#include <cmath>
// #include <omp.h>

Engine::Engine(std::vector<CylPos>&& cylPos):
    cylPos(std::move(cylPos)) {}

void Engine::setOmega(double newOmega) {
    omega = newOmega;
}

void Engine::step(double dt) {
    angle += omega * dt;
    angle = fmod(angle, 2.0 * std::numbers::pi);
    if (angle < 0.0) angle += 2.0 * std::numbers::pi;

    // #pragma omp parallel for
    for (size_t id = 0; id < cylPos.size(); ++id) {
        cylPos[id].cylinder.step(angle + cylPos[id].position, omega);
    }
}
