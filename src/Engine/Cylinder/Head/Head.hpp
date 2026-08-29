#pragma once
#include "Valvetrain/Valvetrain.hpp"
#include "Pipes/Pipe.hpp"

class Head {
public:
    Head(
        double chamberVolume,
        Valvetrain&& intakeValvetrain,
        Valvetrain&& exhaustValvetrain,
        Pipe* intakePipe = nullptr,
        Pipe* exhaustPipe = nullptr
    );

    double getChamberVolume() const;

    double getIntakeLift(double angle) const;
    double getExhaustLift(double angle) const;
    double getIntakeFlowArea(double angle) const;
    double getExhaustFlowArea(double angle) const;

    void setExhaustPipe(Pipe* pipe);
    void setIntakePipe(Pipe* pipe);

private:
    double chamberVolume;
    Valvetrain intakeValvetrain;
    Valvetrain exhaustValvetrain;
    Pipe* intakePipe;
    Pipe* exhaustPipe;
};
