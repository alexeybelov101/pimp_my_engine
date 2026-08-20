#include "CamshaftBuilder.hpp"
#include "Camlobe.hpp"
#include "Camshaft.hpp"
#include <nlohmann/json.hpp>
#include <utility>

using json = nlohmann::json;

Camshaft CamshaftBuilder::build(const json& config) {
    std::vector<Camshaft::LobePos> lobePos;

    const auto& lobeProto = config["lobe"]["prototype"];

    const int lobeCount = config["lobe"]["count"];
    lobePos.reserve(lobeCount);

    for (int i = 0; i < lobeCount; ++i) {
        Camlobe lobe(lobeProto["maxLift"], lobeProto["duration"]);
        lobePos.push_back({std::move(lobe), lobeProto["position"]});
    }

    return Camshaft(std::move(lobePos));
}

