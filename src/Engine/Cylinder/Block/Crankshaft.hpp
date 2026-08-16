#pragma once

class Crankshaft {
public:
    explicit Crankshaft(double radius);

    struct Projections {
        double horizontal;
        double vertical;
    };

    Projections getProjections(double angle) const;

    double getStroke() const;
    double getRadius() const;

    // Высота подъема кривошипа для заданного угла
    double getVertical(double angle) const;
    double getHorizontal(double angle) const;

private:
    double radius;
};
