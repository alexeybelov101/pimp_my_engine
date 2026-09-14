#pragma once
#include "Interfaces/IJunction.hpp"
#include "Interfaces/IBoundary.hpp"
#include <vector>
#include <functional>

class Junction3 : public IJunction {
public:
    explicit Junction3(
        std::vector<std::reference_wrapper<const IBoundary>> boundaries);

    void calculateBoundaryFluxes() const override;

private:
    std::vector<std::reference_wrapper<const IBoundary>> boundaries_;
};
