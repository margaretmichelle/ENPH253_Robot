#include <Arduino.h>
#include <Constants.h>
#include <Motor.h>

Motor::Motor(int pin1, int pin2) : pin1(pin1), pin2(pin2) {
  // No need for pinMode since analogWrite() incorporates it
  pinName1 = (PinName) pin1;
  pinName2 = (PinName) pin2;
  pinMode(pin1, OUTPUT);
  pinMode(pin2,OUTPUT);
  pwm_start(pinName1, DriveMotorPins::MOTOR_FREQ , 0 , RESOLUTION_12B_COMPARE_FORMAT);
  pwm_start(pinName2, DriveMotorPins::MOTOR_FREQ , 0 , RESOLUTION_12B_COMPARE_FORMAT);
}

void Motor::stop() {
  pwm_start(pinName1, DriveMotorPins::MOTOR_FREQ , 0 , RESOLUTION_12B_COMPARE_FORMAT);
  pwm_start(pinName2, DriveMotorPins::MOTOR_FREQ , 0 , RESOLUTION_12B_COMPARE_FORMAT);
}

void Motor::speed(int speed) {
  // Limits
  if (speed > 255) speed = 255;
  if (speed < -255) speed = -255;

  // Write the speeds to the motors
  if (speed > 0) {
    pwm_start(pinName1, DriveMotorPins::MOTOR_FREQ , speed * MAP_8_BIT_TO_12_BIT , RESOLUTION_12B_COMPARE_FORMAT);
    pwm_start(pinName2, DriveMotorPins::MOTOR_FREQ , 0 , RESOLUTION_12B_COMPARE_FORMAT);
  } else {
    pwm_start(pinName1, DriveMotorPins::MOTOR_FREQ , 0 , RESOLUTION_12B_COMPARE_FORMAT);
    pwm_start(pinName2, DriveMotorPins::MOTOR_FREQ , speed * MAP_8_BIT_TO_12_BIT , RESOLUTION_12B_COMPARE_FORMAT);
  }

  previousSpeed = speed;
}
