#include "Pipe.hpp"

Pipe::Pipe(double area, double dx_real, std::vector<Cell>&& cells, std::vector<Flux>&& fluxes)
    : area_(area), dx_real_(dx_real),
        cells_(std::move(cells)), fluxes_(std::move(fluxes)),
        leftBoundary_(this, true), rightBoundary_(this, false) {}

void Pipe::step(double dt) {
    // calculateInternalFluxes();
    updateCells(dt);
}

void Pipe::updateCells(double dt) {
    double vol = area_ * dx_real_;
    for (size_t i = 0; i < cells_.size(); ++i) {
        // Поток слева (i) входит, поток справа (i+1) выходит
        const Flux& f_left = fluxes_[i];
        const Flux& f_right = fluxes_[i + 1];

        cells_[i].rho += (f_left.mass - f_right.mass) * dt / vol;
        cells_[i].rho_u += (f_left.momentum - f_right.momentum) * dt / vol;
        cells_[i].rho_E += (f_left.energy - f_right.energy) * dt / vol;
    }
}

void Pipe::calculateInternalFluxes() {
    HLLCSolver solver;

    for (size_t i = 1; i < cells_.size(); ++i) {
        // Создаём временные границы для соседних ячеек
        // Или используем прямое вычисление между ячейками

        // Прямой вызов HLLC между ячейками
        Flux flux = computeHLLCFlux(cells_[i-1], cells_[i], area_);
        fluxes_[i] = flux;
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

//==============================================================================
