// SPDX-License-Identifier: AGPL-3.0-or-later
#include "GasDynamics.hpp"
#include "Atmosphere/Atmosphere.hpp"
#include "Pipe/Pipe.hpp"
#include "Cylinder/Cylinder.hpp"
#include "Interfaces/IJunction.hpp"
#include <utility>

GasDynamics::GasDynamics(
    std::unique_ptr<Atmosphere> atmosphere,
    std::vector<std::unique_ptr<Pipe>> pipes,
    std::vector<std::unique_ptr<Cylinder>> cylinders,
    std::vector<std::unique_ptr<IJunction>> junctions
):
    atmosphere_(std::move(atmosphere)),
    pipes_(std::move(pipes)),
    cylinders_(std::move(cylinders)),
    junctions_(std::move(junctions)) {}

GasDynamics::GasDynamics(GasDynamics&&) noexcept = default;
GasDynamics& GasDynamics::operator=(GasDynamics&&) noexcept = default;
GasDynamics::~GasDynamics() = default;

void GasDynamics::step(double dt) {
    for (auto& junction : junctions_) {
        junction->calculateBoundaryFluxes();
    }

    for (auto& cylinder : cylinders_) {
        cylinder->step(dt);
    }

    for (auto& pipe : pipes_) {
        pipe->step(dt);
    }

    atmosphere_->step(dt);
}
