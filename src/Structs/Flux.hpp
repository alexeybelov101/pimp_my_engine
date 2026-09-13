#pragma once

struct Flux {
    double mass;        // Поток массы
    double momentum;    // Поток импульса
    double energy;      // Поток энергии

    Flux(double mass = 0.0, double momentum = 0.0, double energy = 0.0):
        mass(mass), momentum(momentum), energy(energy) {}

    Flux operator-() const {
        return Flux(-mass, -momentum, -energy);
    }

    Flux operator-(const Flux& other) const {
        return Flux(
            mass - other.mass,
            momentum - other.momentum,
            energy - other.energy
        );
    }

    Flux operator+(const Flux& other) const {
        return Flux(
            mass + other.mass,
            momentum + other.momentum,
            energy + other.energy
        );
    }
};
