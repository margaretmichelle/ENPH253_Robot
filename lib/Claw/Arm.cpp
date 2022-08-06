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

    returnToHome();
    claw.open();
}