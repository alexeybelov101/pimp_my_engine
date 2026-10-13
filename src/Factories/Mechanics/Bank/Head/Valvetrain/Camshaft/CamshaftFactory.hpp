// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Engine/Mechanics/Bank/Head/Valvetrain/Camshaft.hpp"
#include "Utility/MeasureConverters.hpp"
#include "Templates/FactoryResult.hpp"
#include <nlohmann/json.hpp>
#include <memory>
#include <vector>

namespace MC = MeasureConverters;
using json = nlohmann::json;

class CamshaftFactory {
public:
    static FactoryResult<Camshaft, Camshaft::Lobe> build(const json& config) {
        auto lobes = createLobes(config["lobes"]);

        std::vector<Camshaft::Lobe*> lobes_ptr;
        lobes_ptr.reserve(lobes.size());
        for (auto& lobe : lobes) {
            lobes_ptr.emplace_back(&lobe);
        }

        return FactoryResult<Camshaft, Camshaft::Lobe> {
            make_unique<Camshaft>(
                std::move(lobes)
            ),
            std::move(lobes_ptr)
        };
    }
private:
    static std::vector<Camshaft::Lobe> createLobes(const json& config) {
        std::vector<Camshaft::Lobe> lobes;
        lobes.reserve(config.size());

        for (const auto& lobeProto : config) {
            lobes.emplace_back(
                MC::degToRad(lobeProto["offset"].get<double>() / 2.0),
                MC::mmToM(lobeProto["maxLift"].get<double>()),
                MC::degToRad(lobeProto["duration"].get<double>() / 2.0)
            );
        }

        return lobes;
    }
};
