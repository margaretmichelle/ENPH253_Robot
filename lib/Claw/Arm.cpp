#include <Arm.h>
#include <Claw.h>
#include <Servo.h>

using namespace ArmNS;

Arm::Arm(int armControlPin, Claw claw) : claw(claw), armServo(armControlPin) {
    armServo.write(ARM_UP);
}

void Arm::returnToHome() {
    armServo.write(ARM_UP);
}

void Arm::goDown() {
    armServo.write(ARM_DOWN);
}

int Arm::getPosition() {
    return armServo.getPosition();
}

void Arm::placeObjectInContainer() {
    goDown();
    claw.close();
    returnToHome();
    claw.open();
}