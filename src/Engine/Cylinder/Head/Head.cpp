#include "Head.hpp"

Head::Head(double chamberVolume, Valvetrain&& intakeValvetrain, Valvetrain&& exhaustValvetrain, Pipe&& intakePipe, Pipe&& exhaustPipe):
    chamberVolume(chamberVolume), intakeValvetrain(intakeValvetrain), exhaustValvetrain(exhaustValvetrain), intakePipe(intakePipe), exhaustPipe(exhaustPipe) {}

double Head::getChamberVolume() const {
    return chamberVolume;
}
