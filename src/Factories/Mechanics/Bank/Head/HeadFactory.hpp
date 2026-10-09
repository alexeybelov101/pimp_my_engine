// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Engine/Mechanics/Bank/Head/Head.hpp"
#include "Engine/Mechanics/Bank/Head/Valvetrain/Valvetrain.hpp"
#include "Valvetrain/ValvetrainFactory.hpp"
#include "Utility/MeasureConverters.hpp"
#include <nlohmann/json.hpp>
#include <memory>
#include <vector>

namespace MC = MeasureConverters;
using json = nlohmann::json;

class HeadFactory {
public:
    struct HeadFactoryResult {
        std::unique_ptr<Head> head;
        std::vector<Head::Headlet*> headlets;
        Valvetrain* valvetrain;
    };

    static HeadFactoryResult build(const json& config) {
        auto [valvetrain, links] = ValvetrainFactory::build(config.at("valvetrain"));
        auto valvetrain_ptr = valvetrain.get();

        auto headlets = createHeadlets(
            config.at("headlets"),
            links
        );

        std::vector<Head::Headlet*> headlets_ptr;
        headlets_ptr.reserve(headlets.size());
        for (auto& headlet : headlets) {
            headlets_ptr.emplace_back(&headlet);
        }

        return {
            std::make_unique<Head>(
                MC::mm3ToM3(config.at("chamberVolume").get<double>()),
                std::move(valvetrain),
                std::move(headlets)
            ),
            std::move(headlets_ptr),
            std::move(valvetrain_ptr)
        };
    }
private:
    static std::vector<Head::Headlet> createHeadlets(
        const json& config,
        std::vector<Valvetrain::Link*> links
    ) {
        std::vector<Head::Headlet> headlets;
        headlets.reserve(config.size());

        for (const auto& headletProto : config) {
            headlets.emplace_back(
                links[headletProto.at("intakeLink").get<size_t>()],
                links[headletProto.at("exhaustLink").get<size_t>()]
            );
        }
        return headlets;
    }
};
