// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Bank.hpp"
#include <utility>

Bank::Bank(
    double offset,
    std::unique_ptr<Head>&& head,
    std::unique_ptr<Block>&& block
):
    offset_(offset),
    head_(std::move(head)),
    block_(std::move(block)) {}
