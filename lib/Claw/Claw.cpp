#include <Claw.h>
#include <Arduino.h>



Claw::Claw(int controlPin, int hallEffectPin) : clawServo(controlPin) {
    hallEffectPin = hallEffectPin;
    clawServo.setupServo(ClawNS::CLAW_OPEN);
    
    pinMode(hallEffectPin, INPUT_ANALOG); // might change to internal pullup resistor (need to test)

    magnetFound = false;
}

void Claw::close() {
    clawServo.write(ClawNS::CLAW_CLOSED);
}

void Claw::open() {
    clawServo.write(ClawNS::CLAW_OPEN);
}

int Claw::getPosition() {
    return clawServo.getPosition();
}


