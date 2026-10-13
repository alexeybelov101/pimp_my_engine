// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <memory>
#include <vector>

class Atmosphere;
class Pipe;
class Cylinder;
class IJunction;

class GasDynamics {
public:
    GasDynamics(
        std::unique_ptr<Atmosphere> atmosphere,
        std::vector<std::unique_ptr<Pipe>> pipes,
        std::vector<std::unique_ptr<Cylinder>> cylinders,
        std::vector<std::unique_ptr<IJunction>> junctions
    );

    GasDynamics(GasDynamics&&) noexcept;
    GasDynamics& operator=(GasDynamics&&) noexcept;

    GasDynamics(const GasDynamics&) = delete;
    GasDynamics& operator=(const GasDynamics&) = delete;

    ~GasDynamics();

    void step(double dt);

    const Atmosphere& atmosphere() const { return *atmosphere_; }
    const std::vector<std::unique_ptr<Pipe>>& pipes() const { return pipes_; }
    const std::vector<std::unique_ptr<IJunction>>& junctions() const { return junctions_; }

private:
    std::unique_ptr<Atmosphere> atmosphere_;
    std::vector<std::unique_ptr<Pipe>> pipes_;
    std::vector<std::unique_ptr<Cylinder>> cylinders_;
    std::vector<std::unique_ptr<IJunction>> junctions_;
};
