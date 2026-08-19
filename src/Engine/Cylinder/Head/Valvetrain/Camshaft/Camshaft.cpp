#include "Camshaft.hpp"

Camshaft::Camshaft(std::vector<LobePos>&& lobepos)
    : lobepos(std::move(lobepos)) {}

double Camshaft::getLift(size_t lobeId, double angle) const {
    if (lobeId >= lobepos.size()) {
        return 0.0;
    }

    double relativeAngle = angle - lobepos[lobeId].position;
    return lobepos[lobeId].lobe.getLift(relativeAngle);
}
