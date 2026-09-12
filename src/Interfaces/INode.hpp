#pragma once
#include "IBoundary.hpp"

class INode {
public:
    virtual ~INode() = default;
    virtual const IBoundary& getBoundary(bool isLeft) const = 0;
    virtual void step(double dt) = 0;
};
