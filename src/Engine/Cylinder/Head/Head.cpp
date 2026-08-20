#include "Head.hpp"
#include <utility>

Head::Head(
    double chamberVolume,
    Valvetrain&& intakeValvetrain,
    Valvetrain&& exhaustValvetrain,
    Pipe* intakePipe,
    Pipe* exhaustPipe
) : chamberVolume(chamberVolume),
    intakeValvetrain(std::move(intakeValvetrain)),
    exhaustValvetrain(std::move(exhaustValvetrain)),
    intakePipe(intakePipe),
    exhaustPipe(exhaustPipe) {}

double Head::getChamberVolume() const {
    return chamberVolume;
}

void Head::setIntakePipe(Pipe* pipe) {
    intakePipe = pipe;
}

void Head::setExhaustPipe(Pipe* pipe) {
    exhaustPipe = pipe;
}
