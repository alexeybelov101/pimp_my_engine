#include "Junction3.hpp"
#include "../../Solvers/RhiemannSolver_3x.hpp"

Junction3::Junction3(std::vector<IBoundary>& boundaries):
    boundaries_(boundaries) {}

void Junction3::calculateBoundaryFluxes() {
    std::vector<Flux> fluxes = Solvers::RhiemannSolver_3x(boundaries_);

    for(size_t i = 0; i < boundaries_.size(); ++i) {
        boundaries_[i].setFlux(fluxes[i]);
    }
}
