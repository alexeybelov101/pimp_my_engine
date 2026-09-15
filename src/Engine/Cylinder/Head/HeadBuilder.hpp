// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <nlohmann/json_fwd.hpp>

class ValvetrainBuilder;
class Head;

class HeadBuilder {
public:
    static Head build(const nlohmann::json& config);
};
