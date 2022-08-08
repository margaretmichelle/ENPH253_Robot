#ifndef encoder_h
#define encoder_h

#include <Arduino.h>
#include <OLED.h>

class Encoder{
    public:

    Encoder();

    void pivotAngle(float angleDegrees);

    void driveStraight(float distanceMm, int motorPower, OLED o);
    /**
     * @brief Attach interrupts in begin method which will be used in main 
     * 
     */
    void begin();

    int getLeftPulses(){
        return leftEncoderPulses;
    }

    int getRightPulses(){
        return rightEncoderPulses;
    }

    private:
        /**
         * @brief interrupt increment
         * 
         */
        void leftEncoderPulse();
        /**
         * @brief interrupt increment
         * 
         */
        void rightEncoderPulse();

    volatile long int leftEncoderPulses;
    volatile long int rightEncoderPulses;
    OLED o;
};

#endif