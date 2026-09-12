#include "Junction2.hpp"
#include "../../Solvers/HLLC.hpp"
#include "../../Solvers/HLL.hpp"
#include <algorithm>

Junction2::Junction2(
    std::reference_wrapper<const IBoundary> left,
    std::reference_wrapper<const IBoundary> right
): left_(left), right_(right) {}

void Junction2::calculateBoundaryFluxes() const {
    const Flux flux = Solvers::HLLC(
        left_.get().getState(),
        right_.get().getState(),
        std::min(
            left_.get().getArea(),
            right_.get().getArea()
        )
    );

    left_.get().setFlux(flux);
    right_.get().setFlux(flux);
}
