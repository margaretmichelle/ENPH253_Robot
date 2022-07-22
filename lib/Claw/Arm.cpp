#include <Arm.h>
#include <Claw.h>

using namespace ArmNS;

Arm::Arm(int armControlPin, Claw claw) : claw(claw) {
    this -> controlPin = armControlPin;
    ArmServo.attach(armControlPin);
    ArmServo.write(ARM_UP);
    currentPos =  ARM_UP;
}

void Arm::returnToHome() {
    ArmServo.write(ARM_UP);
    currentPos = ARM_UP;
}

void Arm::goDown() {
    ArmServo.write(ARM_DOWN);
    currentPos = ARM_DOWN;
}

int Arm::getPosition() {
    return currentPos;
}

void Arm::placeObjectInContainer() {
    goDown();
    claw.close();
    returnToHome();
    claw.open();
}