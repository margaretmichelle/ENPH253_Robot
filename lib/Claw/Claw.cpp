#include <Claw.h>
#include <Arduino.h>



Claw::Claw(int controlPin, int openAngle, int closedAngle) : clawServo(controlPin), opened(openAngle), closed(closedAngle) {
    clawServo.setupServo(opened);
    clawServo.stop();
}

void Claw::close() {
    clawServo.write(closed);
}

void Claw::partialClose() {
    clawServo.write(ClawNS::CLAW_PARTIAL_CLOSE);
}

void Claw::open() {
    clawServo.write(opened);
}

int Claw::getPosition() {
    return clawServo.getPosition();
}


