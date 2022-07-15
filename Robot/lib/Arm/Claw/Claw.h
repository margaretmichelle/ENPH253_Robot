#ifndef Claw_h
#define Claw_h
#include <Arduino.h>
#include <Servo.h>
#include <Constants.h>

class Claw{
    public:
    //Constructor
        Claw(int controlPin);

        /**
         * @brief Close the claw
         * 
         */
        void close();

        /**
         * @brief Open the claw
         * 
         */
        void open();

    private:
    int controlPin;
    Servo ClawServo;
};

#endif