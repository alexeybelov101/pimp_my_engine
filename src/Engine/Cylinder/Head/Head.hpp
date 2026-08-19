#pragma once
#include "Valvetrain/Valvetrain.hpp"
#include "Pipes/Pipe.hpp"

class Head {
    public:
        Head(
            double chamberVolume,
            Valvetrain&& intakeValvetrain,
            Valvetrain&& exhaustValvetrain,
            Pipe&& intakePipe,
            Pipe&& exhaustPipe
        );

        double getChamberVolume() const;

    private:
        double chamberVolume;
        Valvetrain intakeValvetrain;
        Valvetrain exhaustValvetrain;
        Pipe intakePipe;
        Pipe exhaustPipe;
};
