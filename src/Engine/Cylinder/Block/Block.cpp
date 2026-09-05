#include "Block.hpp"
#include <utility>
#include <cmath>

Block::Block(double height, double gasketHeight, Piston&& piston, Conrod&& conrod, Crankshaft&& crankshaft):
    height_(height), gasketHeight_(gasketHeight), piston_(std::move(piston)), conrod_(std::move(conrod)), crankshaft_(std::move(crankshaft)) {}

// TODO: оптимизация - sqrt(lambda^2 - sin^2) вычисляется дважды
double Block::getPistonTopPosition(double angle) const {
    double R = crankshaft_.getRadius();
    double L = conrod_.getLength();
    double H = piston_.getCompressionHeight();
    double lambda = L / R;

    double sinA, cosA;
    sincos(angle, &sinA, &cosA);

    return R * (cosA + std::sqrt(lambda * lambda - sinA * sinA)) + H;
}

double Block::getLeverArm(double angle) const {
    double R = crankshaft_.getRadius();
    double L = conrod_.getLength();
    double lambda = L / R;  // отношение длины шатуна к радиусу

    double sinA, cosA;
    sincos(angle, &sinA, &cosA);

    return R * sinA * (1.0 + cosA / std::sqrt(lambda * lambda - sinA * sinA));
}

double Block::getPistonVelocity(double angle, double omega) const {
    return omega * getLeverArm(angle);
}

double Block::getDisplacedVolume(double angle) const {
    double S = piston_.getBoreArea();
    double x_TDC = getTDC();
    double x_current = getPistonTopPosition(angle);

    return S * (x_TDC - x_current);
}

double Block::getSweptVolume() const {
    return piston_.getBoreArea() * crankshaft_.getStroke();
}

double Block::getTDC() const {
    double R = crankshaft_.getRadius();
    double L = conrod_.getLength();
    double H = piston_.getCompressionHeight();

    return H + L + R;
}

double Block::getBDC() const {
    double R = crankshaft_.getRadius();
    double L = conrod_.getLength();
    double H = piston_.getCompressionHeight();

    return H + L - R;
}

double Block::getDeckClearance() const { //недоход
    return height_ - getTDC();
}

double Block::getTotalDeckVolume() const {
    return piston_.getDeckVolume() + (getDeckClearance() + gasketHeight_) * piston_.getBoreArea();
}

double Block::getBoreArea() const {
    return piston_.getBoreArea();
}
