// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once

class Crankshaft {
public:
    explicit Crankshaft(double radius);

    double getStroke() const;
    double getRadius() const;

    // Высота подъема кривошипа для заданного угла
    double getVertical(double angle) const;
    double getHorizontal(double angle) const;

private:
    double radius_;
};
