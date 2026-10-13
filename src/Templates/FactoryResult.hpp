// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <memory>
#include <vector>

template <typename Parent, typename Child>
struct FactoryResult {
    std::unique_ptr<Parent> parent;
    std::vector<Child*> children;
};
