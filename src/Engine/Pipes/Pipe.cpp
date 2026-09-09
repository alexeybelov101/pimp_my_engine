#include "Pipe.hpp"
#include "../../Solvers/HLLC.hpp"

Pipe::Pipe(double area, double dx_real, std::vector<Cell>&& cells, std::vector<Flux>&& fluxes)
    : area_(area), dx_real_(dx_real),
        cells_(std::move(cells)), fluxes_(std::move(fluxes)),
        leftBoundary_(this, true), rightBoundary_(this, false) {}

void Pipe::step(double dt) {
    calculateInternalFluxes();
    updateCells(dt);
}

void Pipe::calculateInternalFluxes() {
    for (size_t i = 1; i < cells_.size(); ++i) {
        Flux flux = Solvers::HLLC(cells_[i-1], cells_[i], area_);
        fluxes_[i] = flux;
    }
}

void Pipe::updateCells(double dt) {
    double vol = area_ * dx_real_;
    for (size_t i = 0; i < cells_.size(); ++i) {
        // Поток слева (i) входит, поток справа (i+1) выходит
        const Flux& f_result = fluxes_[i] - fluxes_[i + 1];

        cells_[i].rho += f_result.mass * dt / vol;
        cells_[i].rho_u += f_result.momentum * dt / vol;
        cells_[i].rho_E += f_result.energy * dt / vol;
    }
}

const IBoundary& Pipe::getLeftBoundary() const {
    return leftBoundary_;
}

const IBoundary& Pipe::getRightBoundary() const {
    return rightBoundary_;
}

// PipeBoundary
//==============================================================================
Pipe::PipeBoundary::PipeBoundary(Pipe* owner, bool isLeft)
            : owner_(owner), isLeft_(isLeft) {}

const Cell Pipe::PipeBoundary::getState() const {
    return isLeft_ ? owner_->cells_.front() : owner_->cells_.back();
}

void Pipe::PipeBoundary::setFlux(const Flux& flux) {
    Flux& owner_flux = isLeft_ ? owner_->fluxes_.front() : owner_->fluxes_.back();
    owner_flux = flux;
}

double Pipe::PipeBoundary::getArea() const {
    return owner_->area_;
}

bool Pipe::PipeBoundary::isLeft() const {
    return isLeft_;
}
//==============================================================================
