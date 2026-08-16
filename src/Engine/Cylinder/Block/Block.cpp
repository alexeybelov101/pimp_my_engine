#include "Block.hpp"
#include <utility>
#include <cmath>

Block::Block(double height, Piston&& piston, Conrod&& conrod, Crankshaft&& crankshaft):
    height(height), piston(std::move(piston)), conrod(std::move(conrod)), crankshaft(std::move(crankshaft)) {}

double Block::getPistonTopPosition(double angle) const {
    Crankshaft::Projections proj = crankshaft.getProjections(angle);
    double L = conrod.getLength();
    double H = piston.getCompressionHeight();

    return proj.vertical + std::sqrt(L * L - proj.horizontal * proj.horizontal) + H;
}

double Block::getPistonVelocity(double angle, double rpm) const {
    double r = crankshaft.getRadius();
    double L = conrod.getLength();
    double lambda = L / r;  // отношение длины шатуна к радиусу
    double omega = 2.0 * M_PI * rpm / 60.0;

    double sinA, cosA;
    sincos(angle, &sinA, &cosA);

    return omega * r * sinA * (1.0 + cosA / std::sqrt(lambda * lambda - sinA * sinA));
}

double Block::getDisplacedVolume(double angle) const {
    double r = crankshaft.getRadius();
    double L = conrod.getLength();
    double H = piston.getCompressionHeight();
    double S = piston.getBoreArea();

    double x_TDC = r + L + H;
    double x_current = getPistonTopPosition(angle);

    return S * (x_TDC - x_current);
}

double Block::getSweptVolume() const {
    return piston.getBoreArea() * crankshaft.getStroke();
}
