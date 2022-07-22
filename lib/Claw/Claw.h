#ifndef claw_h
#define claw_h
#include <Arduino.h>
#include <Servo.h>
#include <Constants.h>

class Claw {
    public:
    //Constructor
        Claw(int controlPin, int hallEffectPin);

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

        /**
         * @brief Get the position of the claw
         * 
         * @return int that represents angle of the claw in degrees
         */
        int getPosition();

        bool wasMagnetFound();

    private:
    int controlPin;
    int hallEffectPin;
    int currentPos;
    Servo clawServo;
    bool magnetFound;
};

#endif