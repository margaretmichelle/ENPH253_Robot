#ifndef arm_h
#define arm_h
#include <Arduino.h>
#include <ServoMotor.h>
#include <Constants.h>
#include <Claw.h>
#include <OLED.h>

class Arm {
    public:
    //Constructor
        Arm(int armControlPin, Claw claw);

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

        void findHome(int minAngle, int maxAngle, OLED o);

    private:
    ServoMotor armServo;
    Claw claw;
};

#endif


