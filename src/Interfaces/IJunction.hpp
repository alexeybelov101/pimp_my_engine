#pragma once

class IJunction {
public:
    virtual ~IJunction() = default;

    virtual void calculateBoundaryFluxes() = 0;
};
