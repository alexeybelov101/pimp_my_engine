#pragma once
#include <vector>
#include "Camlobe.hpp"

class Camshaft {
public:
    struct LobePos {
        Camlobe lobe;
        double position;
    };

    Camshaft(std::vector<LobePos>&& lobepos);

    double getLift(size_t lobeId, double angle) const;

private:
    std::vector<LobePos> lobepos;
};
