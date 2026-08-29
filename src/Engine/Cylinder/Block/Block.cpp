#include "Block.hpp"
#include <utility>
#include <cmath>

Block::Block(double height, double gasketHeight, Piston&& piston, Conrod&& conrod, Crankshaft&& crankshaft):
    height(height), gasketHeight(gasketHeight), piston(std::move(piston)), conrod(std::move(conrod)), crankshaft(std::move(crankshaft)) {}

// TODO: оптимизация - sqrt(lambda^2 - sin^2) вычисляется дважды
double Block::getPistonTopPosition(double angle) const {
    double R = crankshaft.getRadius();
    double L = conrod.getLength();
    double H = piston.getCompressionHeight();
    double lambda = L / R;

    double sinA, cosA;
    sincos(angle, &sinA, &cosA);

    return R * (cosA + std::sqrt(lambda * lambda - sinA * sinA)) + H;
}

double Block::getLeverArm(double angle) const {
    double R = crankshaft.getRadius();
    double L = conrod.getLength();
    double lambda = L / R;  // отношение длины шатуна к радиусу

    double sinA, cosA;
    sincos(angle, &sinA, &cosA);

    return R * sinA * (1.0 + cosA / std::sqrt(lambda * lambda - sinA * sinA));
}

double Block::getPistonVelocity(double angle, double omega) const {
    return omega * getLeverArm(angle);
}

double Block::getDisplacedVolume(double angle) const {
    double S = piston.getBoreArea();
    double x_TDC = getTDC();
    double x_current = getPistonTopPosition(angle);

    return S * (x_TDC - x_current);
}

double Block::getSweptVolume() const {
    return piston.getBoreArea() * crankshaft.getStroke();
}

double Block::getTDC() const {
    double R = crankshaft.getRadius();
    double L = conrod.getLength();
    double H = piston.getCompressionHeight();

    return H + L + R;
}

double Block::getBDC() const {
    double R = crankshaft.getRadius();
    double L = conrod.getLength();
    double H = piston.getCompressionHeight();

    return H + L - R;
}

double Block::getDeckClearance() const { //недоход
    return height - getTDC();
}

double Block::getTotalDeckVolume() const {
    return piston.getDeckVolume() + (getDeckClearance() + gasketHeight) * piston.getBoreArea();
}
