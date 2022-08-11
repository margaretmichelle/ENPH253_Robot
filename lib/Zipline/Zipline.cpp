#include <Constants.h>
#include <Motor.h>
#include <Zipline.h>

Zipline::Zipline(Motor motor) : motor(motor) {
}

void Zipline::extendZipline(int speed, int time) {
    motor.speed(speed);
    delay(time);
}

void Zipline::stopZipline() {
    motor.stop();
}

void Zipline::descendZipline(int speed, int time) {
    motor.speed(-speed);
    delay(time);
}