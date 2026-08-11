#pragma once

class Conrod {
public:
    explicit Conrod(double length_mm);

    double get_length() const { return length_mm; }

private:
    double length_mm;
};
