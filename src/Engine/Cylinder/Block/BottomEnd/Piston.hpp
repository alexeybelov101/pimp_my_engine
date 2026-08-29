#pragma once

class Piston {
    public:
        Piston(double diameter, double compressionHeight, double deckVolume);

        double getBore() const;
        double getCompressionHeight() const;
        double getBoreArea() const;
        double getDeckVolume() const;

    private:
        double diameter;
        double compressionHeight;
        double deckVolume;
};
