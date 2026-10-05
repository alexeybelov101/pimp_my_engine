// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <nlohmann/json_fwd.hpp>
#include <memory>
#include <vector>

class Bank;
class Crankshaft;

class BankBuilder {
public:
    static std::vector<std::unique_ptr<Bank>> build(const nlohmann::json& config, Crankshaft* crankshaft);
};
