// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Engine/Kinematics/Flywheel/Flywheel.hpp"
#include "Crankshaft.hpp"
#include <memory>
#include <vector>
#include <nlohmann/json_fwd.hpp>

class CrankshaftBuilder {
public:
    static std::unique_ptr<Crankshaft> build(const nlohmann::json& config, Flywheel& flywheel);
private:
    static std::vector<Crankshaft::Pin> createPins(const nlohmann::json& config);
};
