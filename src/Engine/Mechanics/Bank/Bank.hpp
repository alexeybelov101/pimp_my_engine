// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <memory>
#include "Head/Head.hpp"
#include "Block/Block.hpp"

class Bank {
public:
    Bank(
        double offset,
        std::unique_ptr<Head>&& head,
        std::unique_ptr<Block>&& block
    );
private:
    const double offset_;
    std::unique_ptr<Head> head_;
    std::unique_ptr<Block> block_;
};

