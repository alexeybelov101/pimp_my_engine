#pragma once
// #include <vector>

struct Cell {
    double rho;      // Плотность
    double rho_u;    // Импульс
    double rho_E;    // Полная энергия

    Cell(double rho, double rho_u, double rho_E) :
        rho(rho), rho_u(rho_u), rho_E(rho_E) {}

    double getPressure(double gamma) const {
        return (gamma - 1.0) * (rho_E - 0.5 * rho_u * rho_u / rho);
    }
};

struct Flux {
    double mass;        // Поток массы
    double momentum;    // Поток импульса
    double energy;      // Поток энергии

    Flux(double mass, double momentum, double energy) :
        mass(mass), momentum(momentum), energy(energy) {}
};

class IBoundary {
public:
    virtual ~IBoundary() = default;
    virtual const Cell getState() const = 0;
    virtual void setFlux(const Flux& flux) = 0;
    virtual double getArea() const = 0;
};

class INode {
public:
    virtual ~INode() = default;
    virtual const IBoundary& getLeftBoundary() const = 0;
    virtual const IBoundary& getRightBoundary() const = 0;
    virtual void step(double dt) = 0;
};

// class ISolver {
// public:
//     virtual ~ISolver() = default;
//     // Решает систему уравнений на стыке нескольких границ
//     virtual std::vector<BoundaryFlux> solve(
//         const std::vector<std::shared_ptr<IBoundary>>& boundaries,
//         double dt
//     ) = 0;
// };

// // Пример простого солвера для соединения двух труб (упрощенный HLLC/Riemann)
// class SimplePipeSolver : public ISolver {
// public:
//     std::vector<BoundaryFlux> solve(const std::vector<std::shared_ptr<IBoundary>>& boundaries, double dt) override {
//         if (boundaries.size() != 2) throw std::runtime_error("SimplePipeSolver requires exactly 2 boundaries");
//
//         auto leftState = boundaries[0]->getState();
//         auto rightState = boundaries[1]->getState();
//
//         // Здесь вызывается ваш HLLC или Roe solver для двух состояний
//         // Результат - поток через границу раздела
//         BoundaryFlux flux = calculateHLLCFlux(leftState, rightState);
//
//         // Возвращаем потоки для каждой границы (они равны по модулю, но противоположны по знаку)
//         return { flux, {-flux.mass, -flux.momentum, -flux.energy} };
//     }
//
// private:
//     BoundaryFlux calculateHLLCFlux(const ConservativeState& L, const ConservativeState& R) {
//         // ... ваша реализация HLLC ...
//         return {0.0, 0.0, 0.0};
//     }
// };
