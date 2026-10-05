// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Head.hpp"
#include "Valvetrain/Valvetrain.hpp"
#include <memory>
#include <vector>
#include <nlohmann/json_fwd.hpp>

class HeadBuilder {
public:
    static std::unique_ptr<Head> build(const nlohmann::json& config);
private:
    static std::vector<Head::Headlet> createHeadlets(
        const nlohmann::json& config,
        Valvetrain* intakeValvetrain,
        Valvetrain* exhaustValvetrain
    );
};
