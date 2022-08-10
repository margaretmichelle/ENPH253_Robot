#include <Arduino.h>
#include <Constants.h>
#include <ServoMotor.h>

ServoMotor::ServoMotor(int controlPin) {
  pinName = (PinName) controlPin;
}

void ServoMotor::setupServo(int angle) {
  pwm_start(pinName, ServoNS::SERVO_FREQ, mapAngleToPulseWidth(angle), MICROSEC_COMPARE_FORMAT);
  currentPos = angle;
}

void ServoMotor::write(int angle) {
  int delayTime = abs(angle - currentPos) * 900 / 180;
  pwm_start(pinName, ServoNS::SERVO_FREQ, mapAngleToPulseWidth(angle), MICROSEC_COMPARE_FORMAT);
  currentPos = angle;
  delay(delayTime);
}

int ServoMotor::mapAngleToPulseWidth(int angle) {
  return ( angle * (ServoNS::MAX_PULSE_WIDTH - ServoNS::MIN_PULSE_WIDTH) / 180 ) + ServoNS::MIN_PULSE_WIDTH;
}

void ServoMotor::stop() {
  delay(200);
  pwm_start(pinName,ServoNS::SERVO_FREQ, 0, MICROSEC_COMPARE_FORMAT);
}
