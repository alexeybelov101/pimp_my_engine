#include "CamshaftBuilder.hpp"
#include "Camlobe.hpp"
#include "Camshaft.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Camshaft CamshaftBuilder::build(const json& config) {
    std::vector<Camshaft::LobePos> lobepos;

    const auto& lobeProto = config["lobes"]["prototype"];

    const int lobeCount = config["lobes"]["count"];
    lobepos.reserve(lobeCount);

    for (int i = 0; i < lobeCount; ++i) {
        Camlobe lobe(lobeProto["maxLift"], lobeProto["duration"]);
        lobepos.push_back({std::move(lobe), lobeProto["position"]});
    }

    return Camshaft(std::move(lobepos));
}

