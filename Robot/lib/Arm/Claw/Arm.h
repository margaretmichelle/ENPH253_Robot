#ifndef Arm_h
#define Arm_h
#include <Arduino.h>
#include <Servo.h>
#include <Constants.h>
#include <Claw.h>

class Arm{
    public:
    //Constructor
        Arm(int controlPin);

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

    private:
    int controlPin;
    Servo ArmServo;
};

#endif


