#pragma once
#include "../../Interfaces/INode.hpp"
#include "../../Structs/Cell.hpp"
#include <utility>

class Atmosphere : public INode {
public:
    Atmosphere();
    ~Atmosphere() override = default;

    const IBoundary& getBoundary(bool isLeft) const override;
    void step(double dt) override;

private:
    class AtmosphereBoundary : public IBoundary {
    public:
        AtmosphereBoundary(Atmosphere* owner, bool isLeft);
        ~AtmosphereBoundary() override = default;

        Cell getState() const override;
        void setFlux(const Flux& flux) const override;
        double getArea() const override;
        bool isLeft() const override;

    private:
        Atmosphere* owner_;
        bool isLeft_;
    };

    std::pair<AtmosphereBoundary, AtmosphereBoundary> boundaries_;
    const Cell cell_;
};
