#include <Arm.h>
#include <Claw.h>
<<<<<<< HEAD

Arm::Arm(int armControlPin, Claw claw, int hallEffectPin) : claw(claw), armServo(armControlPin), hallEffectPin(hallEffectPin) {
    armServo.setupServo(ArmNS::ARM_UP);

    pinMode(hallEffectPin, INPUT);
=======
#include <OLED.h>

using namespace ArmNS;
void magnetInterrupt();

Arm::Arm(int armControlPin, Claw claw) : claw(claw), armServo(armControlPin) {
    armServo.setupServo(ARM_UP);
>>>>>>> a90412d316a8ac95e85e3f6303a477f8f2efa7af
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
<<<<<<< HEAD

    claw.partialClose();

    delay(500);

    if (analogRead(hallEffectPin) < 300) {
        claw.open();
        returnToHome();
        return;
    }

    returnToHome();
    claw.open();
=======
}

void magnetInterrupt() {
    
>>>>>>> a90412d316a8ac95e85e3f6303a477f8f2efa7af
}