// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Engine/Mechanics/Flywheel/Flywheel.hpp"
#include "Engine/Mechanics/Crankshaft/Crankshaft.hpp"
#include "Utility/MeasureConverters.hpp"
#include "Templates/FactoryResult.hpp"
#include <nlohmann/json.hpp>
#include <memory>
#include <vector>

namespace MC = MeasureConverters;
using json = nlohmann::json;

class CrankshaftFactory {
public:
    static FactoryResult<Crankshaft, Crankshaft::Pin> build(const json& config, Flywheel* flywheel) {
        auto pins = createPins(config["pins"]);

        std::vector<Crankshaft::Pin*> pins_ptr;
        pins_ptr.reserve(pins.size());
        for (auto& pin : pins) {
            pins_ptr.emplace_back(&pin);
        }

        return FactoryResult<Crankshaft, Crankshaft::Pin> {
            std::make_unique<Crankshaft>(
                MC::mmToM(config["radius"].get<double>()),
                std::move(pins),
                flywheel
            ),
            std::move(pins_ptr)
        };


    }
private:
    static std::vector<Crankshaft::Pin> createPins(const json& config) {
        std::vector<Crankshaft::Pin> pins;
        pins.reserve(config.size());

        for (const auto& pinProto : config) {
            pins.emplace_back(
                MC::degToRad(pinProto["offset"].get<double>())
            );
        }

        return pins;
    }
};
