#include <Arm.h>
#include <Claw.h>

Arm::Arm(int armControlPin, Claw claw, int hallEffectPin, int upAngle, int downAngle) : 
                        claw(claw), armServo(armControlPin), 
                        hallEffectPin(hallEffectPin), up(upAngle), down(downAngle) {
    armServo.setupServo(up);

    pinMode(hallEffectPin, INPUT);
}

void Arm::returnToHome() {
    armServo.write(up);
}

void Arm::goDown() {
    armServo.write(down);
}

int Arm::getPosition() {
    return armServo.getPosition();
}

void Arm::placeObjectInContainer() {
    goDown();

    delay(500);

    if (analogRead(hallEffectPin) < 300) {
        claw.open();
        returnToHome();
        return;
    }

    claw.close();

    delay(500);

    if (analogRead(hallEffectPin) < 300) {
        claw.open();
        returnToHome();
        return;
    }

    if (up == ArmNS::LEFT_ARM_UP) {
        armServo.write(ArmNS::LEFT_ARM_DROP);
    } else {
        armServo.write(ArmNS::RIGHT_ARM_DROP);
    }

    claw.open();

    returnToHome();
}

void Arm::goThroughArch() {
    if (up == ArmNS::LEFT_ARM_UP) {
        armServo.write(ArmNS::LEFT_ARM_ARCH);
    } else {
        claw.partialClose();
        armServo.write(ArmNS::RIGHT_ARM_ARCH);
    }
}