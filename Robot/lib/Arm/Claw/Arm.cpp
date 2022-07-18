#include <Arm.h>

using namespace ArmConstants;

Arm::Arm(int clawControlPin, int armControlPin){
    this.controlPin = armControlPin;
    ArmServo.attach(armControlPin);
    ArmServo.write(CLAW_UP);
    currentPos =  CLAW_UP;
    ArmClaw(armControlPin);
}

void Arm::returnToHome(){
    ArmServo.write(CLAW_UP);
}

int Arm::getPosition(){
    return currentPos;
}

void Arm::placeObjectInContainer(){
    ArmServo.write(CLAW_DOWN)
    //Add Hall Effect Sensing
    ArmClaw.close();
    returnToHome();
}