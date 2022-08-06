#ifndef encoder_h
#define encoder_h

#include <Arduino.h>

class Encoder{
    public:

    Encoder();

    void pivotAngle(float angleDegrees);

    void driveStraight(float distanceMm, int motorPower);
};

#endif