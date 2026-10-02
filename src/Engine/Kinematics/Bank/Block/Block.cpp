// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Block.hpp"
#include <utility>
#include <cmath>

Block::Block(
    double height,
    double gasketHeight,
    std::vector<Blocklet>&& blocklets
):
    height_(height),
    gasketHeight_(gasketHeight),
    blocklets_(std::move(blocklets)) {
        for (auto& b : blocklets_) b.owner_ = this;
    }

Block::Blocklet::Blocklet(
    Piston&& piston,
    Conrod&& conrod,
    Crankshaft::Pin& pin
):
    owner_(nullptr),
    piston_(std::move(piston)),
    conrod_(std::move(conrod)),
    pin_(pin) {}

// TODO: оптимизация - sqrt(lambda^2 - sin^2) вычисляется дважды
double Block::Blocklet::getPistonTopPosition() const {
    double angle = pin_.getAngle();
    double R = pin_.getThrow();
    double L = conrod_.getLength();
    double H = piston_.getCompressionHeight();
    double lambda = L / R;

    double sinA, cosA;
    sincos(angle, &sinA, &cosA);

    return R * (cosA + std::sqrt(lambda * lambda - sinA * sinA)) + H;
}

double Block::Blocklet::getLeverArm() const {
    double angle = pin_.getAngle();
    double R = pin_.getThrow();
    double L = conrod_.getLength();
    double lambda = L / R;  // отношение длины шатуна к радиусу

    double sinA, cosA;
    sincos(angle, &sinA, &cosA);

    return R * sinA * (1.0 + cosA / std::sqrt(lambda * lambda - sinA * sinA));
}

double Block::Blocklet::getPistonVelocity() const {
    return pin_.getOmega() * getLeverArm();
}

double Block::Blocklet::getDisplacedVolume() const {
    double S = piston_.getBoreArea();
    double x_TDC = getTDC();
    double x_current = getPistonTopPosition();

    return S * (x_TDC - x_current);
}

double Block::Blocklet::getSweptVolume() const {
    return piston_.getBoreArea() * pin_.getThrow() * 2.0;
}

double Block::Blocklet::getTDC() const {
    double R = pin_.getThrow();
    double L = conrod_.getLength();
    double H = piston_.getCompressionHeight();

    return H + L + R;
}

double Block::Blocklet::getBDC() const {
    double R = pin_.getThrow();
    double L = conrod_.getLength();
    double H = piston_.getCompressionHeight();

    return H + L - R;
}

double Block::Blocklet::getDeckClearance() const { //недоход
    return owner_->height_ - getTDC();
}

double Block::Blocklet::getTotalDeckVolume() const {
    return piston_.getDeckVolume() + (getDeckClearance() + owner_->gasketHeight_) * piston_.getBoreArea();
}

double Block::Blocklet::getBoreArea() const {
    return piston_.getBoreArea();
}

void Block::Blocklet::applyForce(double force) {
    pin_.setTorque(force * getLeverArm());
}
