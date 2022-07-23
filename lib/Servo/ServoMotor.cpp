#include <Arduino.h>
#include <Constants.h>
#include <ServoMotor.h>

ServoMotor::ServoMotor(int controlPin) {
  pinName = (PinName) controlPin;
  pinMode(controlPin, OUTPUT);
}
 
void ServoMotor::write(int angle) {
  pwm_start(pinName, ServoNS::SERVO_FREQ, mapAngleToDutyCycle(angle), RESOLUTION_12B_COMPARE_FORMAT);
  currentPos = angle;
}

int ServoMotor::mapAngleToDutyCycle(int angle) {
  return ( angle * (ServoNS::MAX_DUTY_CYCLE - ServoNS::MIN_DUTY_CYCLE) / 180 ) + ServoNS::MIN_DUTY_CYCLE;
}

