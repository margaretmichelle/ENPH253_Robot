#include <Claw.h>

using namespace ClawNS;

Claw::Claw(int controlPin, int hallEffectPin) {
    this -> controlPin = controlPin;
    this -> hallEffectPin = hallEffectPin;
    clawServo.attach(controlPin);
    currentPos = CLAW_OPEN;
    clawServo.write(CLAW_OPEN);
    
    pinMode(hallEffectPin, INPUT_ANALOG); // might change to internal pullup resistor (need to test)
    magnetFound = false;
}

void Claw::close() {
    // Assume CLAW_OPEN > CLAW_CLOSED
    for (int i = CLAW_OPEN; i >= CLAW_CLOSED; i--) {
        if (analogRead(hallEffectPin) < 300) {
            magnetFound = true;
            clawServo.write(CLAW_OPEN);
            currentPos = CLAW_OPEN;
            break;
        }
        clawServo.write(i);
        currentPos = i;
    }
}

void Claw::open() {
    currentPos = CLAW_OPEN;
    clawServo.write(CLAW_OPEN);
}

int Claw::getPosition() {
    return currentPos;
}