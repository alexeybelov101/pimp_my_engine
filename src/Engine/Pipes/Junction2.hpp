#pragma once
#include "../../Interfaces/IJunction.hpp"
#include "../../Interfaces/IBoundary.hpp"
#include <utility>

class Junction2 : public IJunction {
public:
    Junction2(std::pair<IBoundary&, IBoundary&> boundaries);
    ~Junction2() override = default;

    void calculateBoundaryFluxes() override;

private:
    std::pair<IBoundary&, IBoundary&> boundaries_;
};
