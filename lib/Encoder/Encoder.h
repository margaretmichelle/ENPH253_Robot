#ifndef encoder_h
#define encoder_h

#include <Arduino.h>

class Encoder{
    public:

    Encoder();

    void pivotAngle(float angleDegrees);

    void driveStraight(float distanceMm, int motorPower);
    /**
     * @brief Attach interrupts in begin method which will be used in main 
     * 
     */
    void begin();

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
};

#endif