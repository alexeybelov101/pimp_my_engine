// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Bank.hpp"
#include <utility>

Bank::Bank(
    double offset,
    std::unique_ptr<Head> head,
    std::unique_ptr<Block> block
):
    offset_(offset),
    head_(std::move(head)),
    block_(std::move(block)) {}

std::vector<Valvetrain*> Bank::getValvetrains() {
    std::vector<Valvetrain*> result;

    result.push_back(head_->intakeValvetrain_.get());
    result.push_back(head_->exhaustValvetrain_.get());

    return result;
}

std::vector<Head::Headlet*> Bank::getHeadlets() {
    std::vector<Head::Headlet*> headlets;
    headlets.reserve(head_->headlets_.size());

    for (auto& headlet : head_->headlets_) {
        headlets.push_back(&headlet);
    }

    return headlets;
}

std::vector<Block::Blocklet*> Bank::getBlocklets() {
    std::vector<Block::Blocklet*> blocklets;
    blocklets.reserve(block_->blocklets_.size());

    for (auto& blocklet : block_->blocklets_) {
        blocklets.push_back(&blocklet);
    }

    return blocklets;
}
