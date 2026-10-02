// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <nlohmann/json_fwd.hpp>
#include <memory>

class Bank;

class BankBuilder {
public:
    static std::unique_ptr<Bank> build(const nlohmann::json& config);
};
