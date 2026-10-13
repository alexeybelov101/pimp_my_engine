// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Factories/Mechanics/Bank/Head/Valvetrain/Camshaft/CamshaftFactory.hpp"
#include "Engine/Mechanics/Bank/Head/Valvetrain/Camshaft.hpp"
#include "Engine/Mechanics/Bank/Head/Valvetrain/Valve.hpp"
#include "Engine/Mechanics/Bank/Head/Valvetrain/Valvetrain.hpp"
#include "Utility/MeasureConverters.hpp"
#include "Templates/FactoryResult.hpp"
#include <nlohmann/json.hpp>
#include <memory>
#include <cmath>

namespace MC = MeasureConverters;
using json = nlohmann::json;

class ValvetrainFactory {
public:
    static FactoryResult<Valvetrain, Valvetrain::Link> build(const json& config) {
        auto [camshaft, lobes_ptr] = CamshaftFactory::build(config.at("camshaft"));

        auto valves = createValves(config.at("valves"));
        std::vector<Valve*> valves_ptr;
        valves_ptr.reserve(valves.size());
        for (auto& valve : valves) {
            valves_ptr.emplace_back(&valve);
        }

        auto links = createLinks(config.at("links"), lobes_ptr, valves_ptr);
        std::vector<Valvetrain::Link*> links_ptr;
        links_ptr.reserve(links.size());
        for (auto& link : links) {
            links_ptr.emplace_back(&link);
        }

        return FactoryResult<Valvetrain, Valvetrain::Link> {
            std::make_unique<Valvetrain>(
                std::move(camshaft),
                std::move(valves),
                std::move(links)
            ),
            std::move(links_ptr)
        };
    }
private:
    static std::vector<Valve> createValves(const json& config) {
        std::vector<Valve> valves;
        valves.reserve(config.size());

        for (const auto& valveProto : config) {
            valves.emplace_back(
                MC::mmToM(valveProto["headDiameter"].get<double>() / 2.0),
                std::sin(MC::degToRad(valveProto["seatAngle"].get<double>())),
                std::cos(MC::degToRad(valveProto["seatAngle"].get<double>()))
            );
        }
        return valves;
    }

    static std::vector<Valvetrain::Link> createLinks(
        const json& config,
        std::vector<Camshaft::Lobe*> lobes,
        std::vector<Valve*> valves
    ) {
        std::vector<Valvetrain::Link> links;
        links.reserve(config.size());

        for (auto& linkProto : config) {
            std::vector<Camshaft::Lobe*> linkLobes;
            linkLobes.reserve(linkProto["lobes"].size());
            for (auto& lobeId : linkProto["lobes"]) {
                linkLobes.emplace_back(lobes[lobeId]);
            }

            std::vector<Valve*> linkValves;
            linkValves.reserve(linkProto["valves"].size());
            for (auto& valveId : linkProto["valves"]) {
                linkValves.emplace_back(valves[valveId]);
            }

            links.emplace_back(
                std::move(linkLobes),
                std::move(linkValves)
            );
        }

        return links;
    }
};
