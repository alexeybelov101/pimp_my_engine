// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <nlohmann/json_fwd.hpp>
#include <memory>
#include <vector>

class PipeSystem;
class Pipe;
class IJunction;
class Atmosphere;
class Cylinder;

class PipeSystemBuilder {
public:
    static std::unique_ptr<PipeSystem> build(
        const nlohmann::json& config,
        const std::vector<std::unique_ptr<Cylinder>>& cylinders,
        const double dt
    );

private:
    static std::vector<std::unique_ptr<Pipe>> createPipes(const nlohmann::json& config, double dt);

    static std::vector<std::unique_ptr<IJunction>> createJunctions(
        const nlohmann::json& config,
        const Atmosphere& atmosphere,
        const std::vector<std::unique_ptr<Pipe>>& pipes,
        const std::vector<std::unique_ptr<Cylinder>>& cylinders
    );
};
