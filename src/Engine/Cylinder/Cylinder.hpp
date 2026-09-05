#pragma once
#include "Head/Head.hpp"
#include "Block/Block.hpp"
#include "../../Interfaces/INode.hpp"
#include "../../Constants/GasDynamics.hpp"

class Cylinder : public INode {
public:
    Cylinder(
        Head&& head,
        Block&& block,
        double offset = 0.0
    );

    Cylinder(Cylinder&& other) noexcept;

double getEnergy() { return energy_; }

    double getTotalChamberVolume() const;
    double getCompressionRatio() const;
    double getCurrentVolume() const;

    double calculatePressure() const;
    double calculateForceG() const; //Работа над газом
    double calculateForceI() const; //Индикаторная работа
    double calculateTorque() const;

    void setOmega(double omega);
    void setKinematics(double angle, double omega);
    void applyFlux(double dt);
    void resetFlux();

    void step(double dt) override;

    const IBoundary& getLeftBoundary() const override;
    const IBoundary& getRightBoundary() const override;
private:
    class CylinderBoundary : public IBoundary {
    public:
        CylinderBoundary(Cylinder* owner, bool isLeft);

        const Cell getState() const override;
        void setFlux(const Flux& flux) override;
        double getArea() const override;
    private:
        Cylinder* owner_;
        bool isLeft_;
    };

    const double offset_;

    double angle_;
    double omega_;
    Head head_;
    Block block_;

    double mass_;
    double energy_;
    CylinderBoundary leftBoundary_;
    CylinderBoundary rightBoundary_;

    Flux flux_;
};

