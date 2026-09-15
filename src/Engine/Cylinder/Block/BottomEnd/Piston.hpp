// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once

class Piston {
    public:
        Piston(double radius, double compressionHeight, double deckVolume);

        double getBore() const;
        double getCompressionHeight() const;
        double getBoreArea() const;
        double getDeckVolume() const;

    private:
        double radius_;
        double compressionHeight_;
        double deckVolume_;
};
