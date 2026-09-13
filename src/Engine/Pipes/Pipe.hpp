#pragma once
#include "../../Interfaces/INode.hpp"
#include "../../Structs/Cell.hpp"
#include "../../Structs/Flux.hpp"
#include <vector>

class Pipe : public INode {
public:
    Pipe(double area,
         double dx_real,
         std::vector<Cell>&& cells,
         std::vector<Flux>&& fluxes);
    ~Pipe() override = default;

    void step(double dt) override;
    void calculateInternalFluxes();

    const IBoundary& getBoundary(bool isLeft) const override;

private:
    class PipeBoundary : public IBoundary {
    public:
        PipeBoundary(Pipe* owner, bool isLeft);

        Cell getState() const override;
        void setFlux(const Flux& flux) const override;
        double getArea() const override;
        double getAperture() const override;
        bool isLeft() const override;

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
