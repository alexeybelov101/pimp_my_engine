#pragma once

class Piston {
    public:
        Piston(double diameter, double compression_height);

        double get_diameter() const { return diameter_mm; }
        double get_compression_height() const { return compression_height_mm; }

    private:
        double diameter_mm;
        double compression_height_mm;
};
