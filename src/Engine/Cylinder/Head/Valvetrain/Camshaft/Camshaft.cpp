#include "Camshaft.hpp"

Camshaft::Camshaft(std::vector<LobePos>&& lobePos)
    : lobePos(std::move(lobePos)) {}

double Camshaft::getLift(size_t lobeId, double angle) const {
    double relativeAngle = angle + lobePos[lobeId].position;
    return lobePos[lobeId].lobe.getLift(relativeAngle);
}
