#pragma once
#include "Camlobe.hpp"
#include <vector>

class Camshaft {
public:
    struct LobePos {
        Camlobe lobe_;
        double position_;

        LobePos(Camlobe&& lobe, double pos)
            : lobe_(std::move(lobe)), position_(pos) {}
    };

    Camshaft(std::vector<LobePos>&& lobePos);

    double getLift(size_t lobeId, double angle) const;

private:
    std::vector<LobePos> lobePos_;
};
