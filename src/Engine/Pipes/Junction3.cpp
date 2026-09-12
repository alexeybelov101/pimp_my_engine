#include "Junction3.hpp"
#include "../../Solvers/RiemannSolver3x.hpp"
#include <utility>

Junction3::Junction3(
    std::vector<std::reference_wrapper<const IBoundary>> boundaries)
    : boundaries_(std::move(boundaries)) {}

void Junction3::calculateBoundaryFluxes() const {
    // const auto fluxes = Solvers::RiemannSolver3x(boundaries_);
    //
    std::vector fluxes(boundaries_.size(), Flux(3,3,3));

    for (size_t i = 0; i < boundaries_.size(); ++i) {
        boundaries_[i].get().setFlux(fluxes[i]);
    }
}
