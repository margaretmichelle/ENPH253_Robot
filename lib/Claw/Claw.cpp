#include <Claw.h>
#include <Servo.h>
#include <Arduino.h>

Claw::Claw(int controlPin, int hallEffectPin) : clawServo(controlPin) {
    hallEffectPin = hallEffectPin;
    clawServo.write(ClawNS::CLAW_OPEN);
    
    pinMode(hallEffectPin, INPUT_ANALOG); // might change to internal pullup resistor (need to test)
    magnetFound = false;
}

void Claw::close() {
    // Assume CLAW_OPEN > CLAW_CLOSED
    // for (int i = ClawNS::CLAW_OPEN; i >= ClawNS::CLAW_CLOSED; i - 10) {
    //     if (analogRead(hallEffectPin) < 300) {
    //         magnetFound = true;
    //         // clawServo.write(ClawNS::CLAW_OPEN);
    //         // break;
    //     }
    //     clawServo.write(i);
    // }
    clawServo.write(ClawNS::CLAW_CLOSED);
}

void Claw::open() {
    clawServo.write(ClawNS::CLAW_OPEN);
}

int Claw::getPosition() {
    return clawServo.getPosition();
}