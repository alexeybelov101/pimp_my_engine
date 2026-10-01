// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Bank.hpp"
#include <utility>

Bank::Bank(
    double position,
    std::unique_ptr<Head> head,
    std::unique_ptr<Block> block
):
    position_(position),
    head_(std::move(head)),
    block_(std::move(block)) {}
