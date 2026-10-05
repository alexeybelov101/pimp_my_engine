// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Piston.hpp"
#include "Conrod.hpp"
#include "Engine/Kinematics/Crankshaft/Crankshaft.hpp"
#include <memory>
#include <vector>

class Block {
public:
    class Blocklet {
    public:
        explicit Blocklet(
            Piston* piston,
            Conrod* conrod,
            Crankshaft::Pin* pin
        );

        double getPistonTopPosition() const;
        double getPistonVelocity() const;
        double getLeverArm() const;
        double getDisplacedVolume() const;
        double getSweptVolume() const;
        double getTDC() const;
        double getBDC() const;
        double getDeckClearance() const;
        double getDeckClearanceVolume () const;
        double getTotalDeckVolume() const;
        double getBoreArea() const;

        void applyForce(double force);

    private:
        Block* owner_;
        Piston* piston_;
        Conrod* conrod_;
        Crankshaft::Pin* pin_;

        friend class Block;
    };

    Block(
        double height,
        double gasketHeight,
        std::vector<std::unique_ptr<Piston>>&& pistons,
        std::vector<std::unique_ptr<Conrod>>&& conrods,
        std::vector<Blocklet>&& blocklets
    );

private:
    double height_;
    double gasketHeight_;
    std::vector<std::unique_ptr<Piston>> pistons_;
    std::vector<std::unique_ptr<Conrod>> conrods_;
    std::vector<Blocklet> blocklets_;

    friend class Bank;
};
