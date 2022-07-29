#include <Claw.h>
#include <Arduino.h>



Claw::Claw(int controlPin) : clawServo(controlPin) {
    clawServo.setupServo(ClawNS::CLAW_OPEN);
}

void Claw::close() {
    clawServo.write(ClawNS::CLAW_CLOSED);
}

void Claw::partialClose() {
    clawServo.write(ClawNS::CLAW_PARTIAL_CLOSE);
}

void Claw::open() {
    clawServo.write(ClawNS::CLAW_OPEN);
}

int Claw::getPosition() {
    return clawServo.getPosition();
}


