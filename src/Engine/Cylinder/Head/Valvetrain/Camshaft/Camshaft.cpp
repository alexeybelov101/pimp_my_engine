#include "Camshaft.hpp"
#include <numbers>
#include <cmath>

Camshaft::Camshaft(std::vector<LobePos>&& lobePos)
    : lobePos_(std::move(lobePos)) {}

double Camshaft::getLift(size_t lobeId, double angle) const {
    double relativeAngle = fmod(
        angle + lobePos_[lobeId].position_,
        2 * std::numbers::pi
    );

    if (relativeAngle < 0) relativeAngle += 2 * std::numbers::pi;

    return lobePos_[lobeId].lobe_.getLift(relativeAngle);
}
