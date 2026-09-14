#include "PipeSystem.hpp"
#include "Atmosphere/Atmosphere.hpp"
#include "Pipe/Pipe.hpp"
#include "../../Interfaces/IJunction.hpp"
#include <utility>

PipeSystem::PipeSystem(
    std::unique_ptr<Atmosphere> atmosphere,
    std::vector<std::unique_ptr<Pipe>> pipes,
    std::vector<std::unique_ptr<IJunction>> junctions)
    : atmosphere_(std::move(atmosphere)),
      pipes_(std::move(pipes)),
      junctions_(std::move(junctions)) {}

PipeSystem::PipeSystem(PipeSystem&&) noexcept = default;
PipeSystem& PipeSystem::operator=(PipeSystem&&) noexcept = default;
PipeSystem::~PipeSystem() = default;

void PipeSystem::step(double dt) {
    for (auto& junction : junctions_) {
        junction->calculateBoundaryFluxes();
    }

    for (auto& pipe : pipes_) {
        pipe->step(dt);
    }

    atmosphere_->step(dt);
}
