#pragma once
#include "IBoundary.hpp"
#include <utility>

class ISolver {
public:
    virtual ~ISolver() = default;

    // Решает систему уравнений на стыке двух границ
    // Возвращает пару потоков: [поток для левой границы, поток для правой границы]
    virtual std::pair<Flux, Flux> solve(
        const IBoundary& leftBoundary,
        const IBoundary& rightBoundary
    ) = 0;
};
