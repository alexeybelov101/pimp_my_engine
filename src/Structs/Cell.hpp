#pragma once

struct Cell {
    double rho;      // Плотность
    double rho_u;    // Импульс
    double rho_E;    // Полная энергия

    Cell(double rho = 0.0, double rho_u = 0.0, double rho_E = 0.0):
        rho(rho), rho_u(rho_u), rho_E(rho_E) {}

    double getPressure(double gamma) const {
        return (gamma - 1.0) * (rho_E - 0.5 * rho_u * rho_u / rho);
    }
};
