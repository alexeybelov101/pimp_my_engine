// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Camshaft.hpp"
#include <memory>
#include <vector>
#include <nlohmann/json_fwd.hpp>

class CamshaftBuilder {
public:
    static std::unique_ptr<Camshaft> build(const nlohmann::json& config);
private:
    static std::vector<Camshaft::Lobe> createLobes(const nlohmann::json& config);
};
