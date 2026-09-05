#pragma once

struct Flux {
    double mass;        // Поток массы
    double momentum;    // Поток импульса
    double energy;      // Поток энергии

    Flux(double mass = 0.0, double momentum = 0.0, double energy = 0.0):
        mass(mass), momentum(momentum), energy(energy) {}
};
