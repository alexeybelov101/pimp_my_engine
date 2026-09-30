// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Bank.hpp"
#include <utility>

Bank::Bank(double position, Head&& head, Block&& block):
    position_(position),
    head_(std::move(head)),
    block_(std::move(block)) {}

void Bank::step(double /*dt*/) {}
