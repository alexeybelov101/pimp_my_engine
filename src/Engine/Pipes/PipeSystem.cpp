#include "PipeSystem.hpp"

PipeSystem::PipeSystem(std::vector<Pipe> pipes, std::vector<IJunction>&& junctions):
    atmosphere_(Atmosphere()), pipes_(pipes), junctions_(std::move(junctions)) {}

void PipeSystem::step(double dt) {
    calculateBoundaryFluxes();

    for (auto& pipe : pipes_) {
        pipe.step(dt);
    }
}

void PipeSystem::calculateBoundaryFluxes() {
    for (auto& junction : junctions_) {
        junction.calculateBoundaryFluxes();
    }
}
