// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <memory>
#include <vector>
#include "Head/Head.hpp"
#include "Block/Block.hpp"

class Bank {
public:
    Bank(
        double offset,
        std::unique_ptr<Head> head,
        std::unique_ptr<Block> block
    );

private:
    const double offset_;
    std::unique_ptr<Head> head_;
    std::unique_ptr<Block> block_;

    std::vector<Valvetrain*> getValvetrains();
    std::vector<Head::Headlet*> getHeadlets();
    std::vector<Block::Blocklet*> getBlocklets();
    friend class KinematicsBuilder;
    friend class PipeSystemBuilder;
};

