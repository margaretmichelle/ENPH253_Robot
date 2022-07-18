#include <Claw.h>

using namespace ClawConstants;

Claw::Claw(int controlPin){
    this.controlPin = controlPin;
    clawServo.attach(controlPin);
    currentPos = CLAW_OPEN;
    clawServo.write(CLAW_OPEN);
}

void Claw::close(){
    currentPos = CLAW_OPEN;
    clawServo.write(CLAW_OPEN);
}

void Claw::open(){
    currentPos = CLAW_CLOSED;
    clawServo.write(CLAW_CLOSED);
}

int Claw::getPosition(){
    return currentPos;
}