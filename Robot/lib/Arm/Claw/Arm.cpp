#include <Arm.h>

using namespace ArmConstants;

Arm::Arm(int clawControlPin, int armControlPin){
    this -> controlPin = armControlPin;
    ArmServo.attach(armControlPin);
    ArmServo.write(ARM_UP);
    currentPos =  ARM_UP;
    ArmClaw(clawControlPin);
}

void Arm::returnToHome(){
    ArmServo.write(ARM_UP);
    currentPos = ARM_UP;
}

void Arm::goDown(){
    //Assuming ARM_UP < ARM_DOWN
    for (int i = ARM_UP; i < ARM_DOWN; i++){
        ArmServo.write(i);
        //Add Hall Effect Sensing
    }
    ArmServo.write(ARM_DOWN);
    currentPos = ARM_DOWN;
}

int Arm::getPosition(){
    return currentPos;
}

void Arm::placeObjectInContainer(){
    goDown();
    //Add Hall Effect Sensing
    ArmClaw.close();
    returnToHome();
}