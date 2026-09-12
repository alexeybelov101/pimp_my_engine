#pragma once
#include "../Structs/Cell.hpp"
#include "../Structs/Flux.hpp"

class IBoundary {
public:
    virtual ~IBoundary() = default;
    virtual Cell getState() const = 0;
    virtual void setFlux(const Flux& flux) const = 0;
    virtual double getArea() const = 0;
    virtual bool isLeft() const = 0;
};
