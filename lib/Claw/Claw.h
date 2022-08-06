#ifndef claw_h
#define claw_h
#include <Arduino.h>
#include <ServoMotor.h>
#include <Constants.h>

class Claw {
    public:
    //Constructor
        Claw(int controlPin, int openAngle, int closedAngle);

        /**
         * @brief Close the claw
         * 
         */
        void close();

        /**
         * @brief partially close claw to 70 degrees
         */
        void partialClose();

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

    private:
    ServoMotor clawServo;
    int opened;
    int closed;
};

#endif