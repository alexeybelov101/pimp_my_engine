#include "Pipe.hpp"
#include "../../../Solvers/HLLC.hpp"
#include <cstddef>

Pipe::Pipe(
    double area,
    double dx_real,
    std::vector<Cell>&& cells,
    std::vector<Flux>&& fluxes
):  area_(area),
    dx_real_(dx_real),
    cells_(std::move(cells)),
    fluxes_(std::move(fluxes)),
    leftBoundary_(this, true),
    rightBoundary_(this, false) {}

void Pipe::step(double dt) {
    calculateInternalFluxes();
    updateCells(dt);
}

void Pipe::calculateInternalFluxes() {
    for (size_t i = 1; i < cells_.size(); ++i) {
        fluxes_[i] = Solvers::HLLC(cells_[i - 1], cells_[i], area_).flux;
    }
}

void Pipe::updateCells(double dt) {
    const double vol = area_ * dx_real_;
    for (size_t i = 0; i < cells_.size(); ++i) {
        const Flux f = fluxes_[i] - fluxes_[i + 1];

        cells_[i].rho   += f.mass     * dt / vol;
        cells_[i].rho_u += f.momentum * dt / vol;
        cells_[i].rho_E += f.energy   * dt / vol;
    }
}

const IBoundary& Pipe::getBoundary(bool isLeft) const {
    return isLeft ? leftBoundary_ : rightBoundary_;
}

// PipeBoundary
//==============================================================================
Pipe::PipeBoundary::PipeBoundary(Pipe* owner, bool isLeft)
    : owner_(owner), isLeft_(isLeft) {}

Cell Pipe::PipeBoundary::getState() const {
    return isLeft_ ? owner_->cells_.front() : owner_->cells_.back();
}

void Pipe::PipeBoundary::setFlux(const Flux& flux) const {
    Flux& owner_flux = isLeft_ ? owner_->fluxes_.front() : owner_->fluxes_.back();
    owner_flux = flux;
}

double Pipe::PipeBoundary::getArea() const {
    return owner_->area_;
}

double Pipe::PipeBoundary::getAperture() const {
    return owner_->area_;
}

bool Pipe::PipeBoundary::isLeft() const {
    return isLeft_;
}
