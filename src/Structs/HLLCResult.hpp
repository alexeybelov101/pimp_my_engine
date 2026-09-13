#pragma once
#include "Flux.hpp"

struct HLLCResult {
    Flux flux;
    double p_star;

    HLLCResult(Flux flux, double p_star):
        flux(flux), p_star(p_star) {}

    HLLCResult():
        flux(0.0, 0.0, 0.0), p_star(0.0) {}
};
