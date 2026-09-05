#pragma once
#include "../../Interfaces/INode.hpp"

#include <vector>

class Pipe : public INode {
public:
    Pipe(double area, double dx_real, std::vector<Cell>&& cells, std::vector<Flux>&& fluxes);
    ~Pipe() override = default;

    void step(double dt) override;
    void calculateInternalFluxes();

    const IBoundary& getLeftBoundary() const override;
    const IBoundary& getRightBoundary() const override;

private:
    class PipeBoundary : public IBoundary {
    public:
        PipeBoundary(Pipe* owner, bool isLeft)
            : owner_(owner), isLeft_(isLeft) {}

        const Cell getState() const override {
            return isLeft_ ? owner_->cells_.front() : owner_->cells_.back();
        }

        void setFlux(const Flux& flux) override {
            Flux& owner_flux = isLeft_ ? owner_->fluxes_.front() : owner_->fluxes_.back();
            owner_flux = flux;
        }

        double getArea() const override { return owner_->area_; }

    private:
        Pipe* owner_;
        bool isLeft_;
    };

    double area_;
    double dx_real_;

    std::vector<Cell> cells_;
    std::vector<Flux> fluxes_;

    PipeBoundary leftBoundary_;
    PipeBoundary rightBoundary_;

    void updateCells(double dt);
};
