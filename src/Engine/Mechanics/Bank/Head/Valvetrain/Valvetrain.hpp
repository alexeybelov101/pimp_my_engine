// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Camshaft.hpp"
#include "Valve.hpp"
#include <memory>
#include <vector>

class Valvetrain {
public:
    class Link {
    public:
        Link(
            std::vector<Camshaft::Lobe*> lobes,
            std::vector<Valve*> valves
        );

        double getTotalFlowArea() const;
        double getTotalValveArea() const;

    private:
        Valvetrain* owner_;
        std::vector<Camshaft::Lobe*> lobes_;
        std::vector<Valve*> valves_;

        friend class Valvetrain;
    };

    Valvetrain(
        std::unique_ptr<Camshaft> camshaft,
        std::vector<Valve>&& valves,
        std::vector<Link>&& links
    );

    double getAngle() const;
    void setAngle(double angle);

private:
    std::unique_ptr<Camshaft> camshaft_;
    std::vector<Valve> valves_;
    std::vector<Link> links_; //links zwo, drei, vier
};
