// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Interfaces/IJunction.hpp"
#include "Interfaces/IBoundary.hpp"
#include <functional>

class Junction2 : public IJunction {
public:
    Junction2(
        std::reference_wrapper<const IBoundary> left,
        std::reference_wrapper<const IBoundary> right
    );

    void calculateBoundaryFluxes() const override;

private:
    std::reference_wrapper<const IBoundary> left_;
    std::reference_wrapper<const IBoundary> right_;
};
