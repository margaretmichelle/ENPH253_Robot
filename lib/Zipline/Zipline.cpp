#include <Constants.h>
#include <Motor.h>
#include <Zipline.h>

Zipline::Zipline(Motor motor) : motor(motor) {
    pinMode(ZiplineNS::ZIPLINE_MICROSWITCH_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(ZiplineNS::ZIPLINE_MICROSWITCH_PIN), std::bind(&Zipline::stopZipline, this), FALLING);
}

void Zipline::extendZipline(int speed) {
    motor.speedZipline(speed);
}

void Zipline::stopZipline() {
    motor.stopZipline();
}