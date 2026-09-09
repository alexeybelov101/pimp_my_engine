#pragma once
#include "../../Interfaces/INode.hpp"
#include <utility>

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
        AtmosphereBoundary(Atmosphere* owner, bool isLeft);
        ~AtmosphereBoundary() override = default;
        const Cell getState() const override;
        void setFlux(const Flux& flux) override;
        double getArea() const override;
        bool isLeft() const override;
    private:
        Atmosphere* owner_;
        bool isLeft_;
    };

    std::pair<AtmosphereBoundary, AtmosphereBoundary> boundaries_;
    const Cell cell_;
};
