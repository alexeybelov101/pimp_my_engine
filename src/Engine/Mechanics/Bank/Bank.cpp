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
    block_(std::move(block)) {
        head_->valvetrain_->bankOffset_ = offset_ * 0.5;
        block_->bankOffset_ = offset_;
    }
