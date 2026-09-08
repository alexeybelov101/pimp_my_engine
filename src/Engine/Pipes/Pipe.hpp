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
        PipeBoundary(Pipe* owner, bool isLeft);

        const Cell getState() const override;
        void setFlux(const Flux& flux) override;
        double getArea() const override;

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
