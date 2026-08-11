#pragma once
#include "Valvetrain/Valvetrain.hpp"
#include "Pipes/Pipe.hpp"

class Head {
    public:
        Head(
            Valvetrain& intake_valvetrain,
            Valvetrain& exhaust_valvetrain,
            Pipe& intake_pipe,
            Pipe& exhaust_pipe
        );


    private:
        Valvetrain& intake_valvetrain;
        Valvetrain& exhaust_valvetrain;
        Pipe& intake_pipe;
        Pipe& exhaust_pipe;
};
