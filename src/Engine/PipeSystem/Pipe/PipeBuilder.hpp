// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <nlohmann/json_fwd.hpp>
#include <memory>

class Pipe;

class PipeBuilder {
public:
    static std::unique_ptr<Pipe> build(const nlohmann::json& config, double dt);
};
