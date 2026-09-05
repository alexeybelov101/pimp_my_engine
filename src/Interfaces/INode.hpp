#pragma once
#include "IBoundary.hpp"

class INode {
public:
    virtual ~INode() = default;
    virtual const IBoundary& getLeftBoundary() const = 0;
    virtual const IBoundary& getRightBoundary() const = 0;
    virtual void step(double dt) = 0;
};
