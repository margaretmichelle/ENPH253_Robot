#ifndef encoder_h
#define encoder_h

#include <Arduino.h>

class Encoder{
    public:

    Encoder();

    int * changeInPosition();

    void driveStraight(int distance, int motorPower);
};

#endif