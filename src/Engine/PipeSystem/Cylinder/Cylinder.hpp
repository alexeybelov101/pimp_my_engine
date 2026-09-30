// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once

#include "Engine/Kinematics/Bank/Head/Head.hpp"
#include "Engine/Kinematics/Bank/Block/Block.hpp"
#include "Interfaces/INode.hpp"
#include "Constants/GasDynamics.hpp"

class Cylinder : public INode {
public:
    Cylinder(
        Head::Headlet& headlet,
        Block::Blocklet& blocklet
    );

    Cylinder(Cylinder&& other) noexcept;

    double getTotalChamberVolume() const;
    double getCompressionRatio() const;
    double getCurrentVolume() const;

    double calculatePressure() const;
    double calculateForceG() const; //Работа над газом
    double calculateForceI() const; //Индикаторная работа
    double calculateTorque() const;

    void applyFlux(double dt);
    void resetFlux();

    void step(double dt) override;

    const IBoundary& getBoundary(bool isLeft) const override;
private:
    class CylinderBoundary : public IBoundary {
    public:
        CylinderBoundary(Cylinder* owner, bool isLeft);

        Cell getState() const override;
        void setFlux(const Flux& flux) const override;
        double getArea() const override;
        double getAperture() const override;
        bool isLeft() const override;
    private:
        Cylinder* owner_;
        bool isLeft_;
    };

    Head::Headlet& headlet_;
    Block::Blocklet& blocklet_;

    double mass_;
    double energy_;
    CylinderBoundary leftBoundary_;
    CylinderBoundary rightBoundary_;

    Flux flux_;
};

