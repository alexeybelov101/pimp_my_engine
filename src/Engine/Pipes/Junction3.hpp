#pragma once
#include "../../Interfaces/IJunction.hpp"
#include "../../Interfaces/IBoundary.hpp"
#include <vector>

class Junction3 : public IJunction {
public:
    Junction3(std::vector<IBoundary>& boundaries);
    ~Junction3() override = default;

    void calculateBoundaryFluxes() override;

private:
    std::vector<IBoundary>& boundaries_;
};
