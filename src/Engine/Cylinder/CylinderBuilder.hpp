// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <nlohmann/json_fwd.hpp>
#include <memory>

class Cylinder;

class CylinderBuilder {
public:
    static std::unique_ptr<Cylinder> build(const nlohmann::json& config, double offset = 0.0);
};
