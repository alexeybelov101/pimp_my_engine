// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Junction2.hpp"
#include "Solvers/HLLC.hpp"
#include "Solvers/Wall.hpp"
#include <algorithm>

Junction2::Junction2(
    std::reference_wrapper<const IBoundary> left,
    std::reference_wrapper<const IBoundary> right
): left_(left), right_(right) {}

void Junction2::calculateBoundaryFluxes() const {
    const double Ap_L = left_.get().getAperture();
    const double Ap_R = right_.get().getAperture();
    const double Ap_flow = std::min(Ap_L, Ap_R);

    const double A_L = left_.get().getArea();
    const double A_R = right_.get().getArea();

    Flux f_L, f_R;
    if (Ap_flow == 0) {
        if (std::isfinite(A_L)) f_L = Solvers::Wall(left_.get().getState(), A_L);
        if (std::isfinite(A_R)) f_R = Solvers::Wall(right_.get().getState(), A_R);
    } else {
        const HLLCResult result = Solvers::HLLC(
            left_.get().getState(),
            right_.get().getState(),
            Ap_flow
        );
        const double p_star = result.p_star;

        f_L = result.flux;
        f_R = result.flux;

        if (std::isfinite(A_L)) f_L.momentum += p_star * (A_L - Ap_flow);
        if (std::isfinite(A_R)) f_R.momentum += p_star * (A_R - Ap_flow);
    }

    left_.get().setFlux(f_L);
    right_.get().setFlux(f_R);
}
