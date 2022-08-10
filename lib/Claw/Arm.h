#ifndef arm_h
#define arm_h
#include <Arduino.h>
#include <ServoMotor.h>
#include <Constants.h>
#include <Claw.h>

class Arm {
    public:
    //Constructor
        Arm(int armControlPin, Claw claw, int hallEffectPin, int upAngle, int downAngle);

        /**
         * @brief grab totem and place in the basket
         * 
         */
        void placeObjectInContainer();

        /**
         * @brief return arm to "home" position
         * 
         */
        void returnToHome();

        /**
         * @brief Put arm in "down" position to pick up object
         * 
         */
        void goDown();

        /**
         * @brief Get the position of the arm
         * 
         * @return int that represents angle of the arm in degrees
         */
        int getPosition();

        void goThroughArch();

    private:
    int hallEffectPin;
    ServoMotor armServo;
    Claw claw;
    int up;
    int down;
};

#endif


