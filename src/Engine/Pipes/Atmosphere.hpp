#pragma once
#include "../../Interfaces/INode.hpp"

class Atmosphere : public INode {
public:
    Atmosphere();
    ~Atmosphere() override = default;
    const IBoundary& getLeftBoundary() const override;
    const IBoundary& getRightBoundary() const override;

    void step(double dt) override {};

private:
    class AtmosphereBoundary : public IBoundary {
    public:
        AtmosphereBoundary(Atmosphere* owner);
        ~AtmosphereBoundary() override = default;
        const Cell getState() const override;
        void setFlux(const Flux& flux) override;
        double getArea() const override;
    private:
        Atmosphere* owner_;
    };

    AtmosphereBoundary boundary_;
    const Cell cell_;
};
