#pragma once

#include "../../Interfaces/IJunction.hpp"
#include "Pipe.hpp"
#include "Atmosphere.hpp"

#include <vector>

class PipeSystem {
public:
    PipeSystem(std::vector<Pipe> pipes, std::vector<IJunction>&& junctions);

    void step(double dt);
    void calculateBoundaryFluxes();

private:
    Atmosphere atmosphere_;
    std::vector<Pipe> pipes_;
    std::vector<IJunction> junctions_;
};
