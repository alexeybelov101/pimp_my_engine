#pragma once

class Conrod {
public:
    explicit Conrod(double length);

    double getLength() const;

private:
    double length_;
};
