// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <vector>

class Camshaft {
public:
    class Lobe {
    public:
        Lobe(
            double offset,
            double maxLift,
            double duration
        );

        double getLift() const;

    private:
        Camshaft* owner_;
        double offset_;
        double maxLift_;
        double duration_;

        friend class Camshaft;
    };

    Camshaft(std::vector<Lobe>&& lobes);

    double getAngle() const;
    void setAngle(double angle);

private:
    double angle_;
    std::vector<Lobe> lobes_;

    std::vector<Lobe*> getLobes();
    friend class ValvetrainBuilder;
};
