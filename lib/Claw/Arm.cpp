#include <Arm.h>
#include <Claw.h>

Arm::Arm(int armControlPin, Claw claw, int hallEffectPin) : claw(claw), armServo(armControlPin), hallEffectPin(hallEffectPin) {
    armServo.setupServo(ArmNS::ARM_UP);

    pinMode(hallEffectPin, INPUT);
}

void Arm::returnToHome() {
    armServo.write(ArmNS::ARM_UP);
}

void Arm::goDown() {
    armServo.write(ArmNS::ARM_DOWN);
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

    delay(500);

    if (analogRead(hallEffectPin) < 300) {
        claw.open();
        returnToHome();
        return;
    }

    claw.partialClose();

    delay(500);

    if (analogRead(hallEffectPin) < 300) {
        claw.open();
        returnToHome();
        return;
    }

    returnToHome();
    claw.open();
}