// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Engine/Mechanics/Drive/Drive.hpp"
#include "Engine/Mechanics/Bank/Head/Valvetrain/Valvetrain.hpp"
#include <nlohmann/json.hpp>
#include <utility>

using json = nlohmann::json;

class DriveFactory {
public:
    static Drive build(Crankshaft* crankshaft, std::vector<Valvetrain*> valvetrains) {
        return Drive(
            crankshaft,
            std::move(valvetrains)
        );
    }
};
