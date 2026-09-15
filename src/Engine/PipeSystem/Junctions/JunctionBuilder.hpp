// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <nlohmann/json_fwd.hpp>
#include <memory>
#include <vector>
#include <functional>

class IBoundary;
class IJunction;
class Atmosphere;
class Pipe;
class Cylinder;

class JunctionBuilder {
public:
    static std::unique_ptr<IJunction> build(
        const nlohmann::json& config,
        const Atmosphere& atmosphere,
        const std::vector<std::unique_ptr<Pipe>>& pipes,
        const std::vector<std::unique_ptr<Cylinder>>& cylinders
    );

private:
    static std::vector<std::reference_wrapper<const IBoundary>> getBoundaries(
        const nlohmann::json& config,
        const Atmosphere& atmosphere,
        const std::vector<std::unique_ptr<Pipe>>& pipes,
        const std::vector<std::unique_ptr<Cylinder>>& cylinders
    );
};
