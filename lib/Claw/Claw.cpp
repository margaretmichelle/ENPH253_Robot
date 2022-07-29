#include <Claw.h>
#include <Arduino.h>



<<<<<<< HEAD
Claw::Claw(int controlPin) : clawServo(controlPin) {
    clawServo.setupServo(ClawNS::CLAW_OPEN);
=======
Claw::Claw(int controlPin, int hallEffectPin) : clawServo(controlPin) {
    hallEffectPin = hallEffectPin;
    clawServo.setupServo(ClawNS::CLAW_OPEN);
    
    pinMode(hallEffectPin, INPUT_ANALOG); // might change to internal pullup resistor (need to test)

    magnetFound = false;
>>>>>>> a90412d316a8ac95e85e3f6303a477f8f2efa7af
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


