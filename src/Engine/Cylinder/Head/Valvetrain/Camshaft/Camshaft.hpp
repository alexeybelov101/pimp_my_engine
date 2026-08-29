#pragma once
#include <vector>
#include "Camlobe.hpp"

class Camshaft {
public:
    struct LobePos {
        Camlobe lobe;
        double position;

        LobePos(Camlobe&& lobe, double pos)
            : lobe(std::move(lobe)), position(pos) {}
    };

    Camshaft(std::vector<LobePos>&& lobePos);

    double getLift(size_t lobeId, double angle) const;

private:
    std::vector<LobePos> lobePos;
};
