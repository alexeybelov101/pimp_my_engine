#include "Junction2.hpp"
#include "../../Solvers/HLLC.hpp"
#include <algorithm>

Junction2::Junction2(std::pair<IBoundary&, IBoundary&> boundaries):
    boundaries_(boundaries) {}

void Junction2::calculateBoundaryFluxes() {
    Flux flux = Solvers::HLLC(
        boundaries_.first.getState(),
        boundaries_.second.getState(),
        std::min(
            boundaries_.first.getArea(),
            boundaries_.second.getArea()
        )
    );

    boundaries_.first.setFlux(flux);
    boundaries_.second.setFlux(flux);
}

