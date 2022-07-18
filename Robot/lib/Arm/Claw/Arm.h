#ifndef arm_h
#define arm_h
#include <Arduino.h>
#include <Servo.h>
#include <Constants.h>
#include <Claw.h>

class Arm{
    public:
    //Constructor
        Arm(int clawControlPin, int armControlPin);

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
         * @brief Get the position of the arm
         * 
         * @return int that represents angle of the arm in degrees
         */
        int getPosition();

    private:
    int controlPin;
    int currentPos;
    Servo ArmServo;
    Claw ArmClaw;
};

#endif


