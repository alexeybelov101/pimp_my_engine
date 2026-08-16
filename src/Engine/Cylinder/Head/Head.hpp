#pragma once
#include "Valvetrain/Valvetrain.hpp"
#include "Pipes/Pipe.hpp"

class Head {
    public:
        Head(
            const double chamber_volume_cc,
            const Valvetrain& intake_valvetrain,
            const Valvetrain& exhaust_valvetrain,
            const Pipe& intake_pipe,
            const Pipe& exhaust_pipe
        );

        double get_chamber_volume() const { return chamber_volume_cc; }

    private:
        const double chamber_volume_cc;
        const Valvetrain& intake_valvetrain;
        const Valvetrain& exhaust_valvetrain;
        const Pipe& intake_pipe;
        const Pipe& exhaust_pipe;
};
