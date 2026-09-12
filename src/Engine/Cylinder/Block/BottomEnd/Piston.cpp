#include "Piston.hpp"
#include <numbers>

Piston::Piston(double radius, double compressionHeight, double deckVolume) :
    radius_(radius), compressionHeight_(compressionHeight), deckVolume_(deckVolume) {}

double Piston::getBore() const {
    return radius_ * 2.0;
}

double Piston::getCompressionHeight() const {
    return compressionHeight_;
}

double Piston::getBoreArea() const {
    return std::numbers::pi * radius_ * radius_;
}

double Piston::getDeckVolume() const {
    return deckVolume_;
}
