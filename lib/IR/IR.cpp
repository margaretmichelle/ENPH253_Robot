// #include <Arduino.h>
// #include <Constants.h>
// #include <Motor.h>
// #include <IR.h>
// #include <math.h>

// IR::IR(Motor leftMotor, Motor rightMotor, int motorSpeed):leftMotor(leftMotor), rightMotor(rightMotor), motorSpeed(motorSpeed){
//   leftSensor = IRFollowerNS::LEFT_IR_SENSOR;
//   middleSensor = IRFollowerNS::MIDDLE_IR_SENSOR;
//   rightSensor = IRFollowerNS::RIGHT_IR_SENSOR;
//   lastReadTime = 0;

//   pinMode(leftSensor, INPUT_PULLUP);
//   pinMode(middleSensor, INPUT_PULLUP);
//   pinMode(rightSensor,INPUT_PULLUP);
// }

// void IR::followIR() {
//     getLeftSensorVal();
//     getMiddleSensorVal();
//     getRightSensorVal();
//     currentTimeUS = getCurrentMicros();

//     if(currentTimeUS - lastReadTime >= IRFollowerNS::TIME_BETWEEN_UPDATES_US) {
//         lastReadTime = currentTimeUS;

//         if(middleIRReading > leftIRReading && middleIRReading > rightIRReading && fabs(leftIRReading - rightIRReading) <= IRFollowerNS::IR_DIFF_THRESHOLD) {
//             leftMotorSpeed = motorSpeed;
//             rightMotorSpeed = motorSpeed;
//         } else {
//             if(leftIRReading > rightIRReading) {
//                 leftMotorSpeed = motorSpeed + IRFollowerNS::MOTOR_SPEED_INCREMENT;
//             } else {
//                 rightMotorSpeed = motorSpeed + IRFollowerNS::MOTOR_SPEED_INCREMENT;
//             }
//         }

//         leftMotor.speed(leftMotorSpeed);
//         rightMotor.speed(rightMotorSpeed);
//     }
// };

// double IR::readIRSensor(int pinNumber){
//     return analogRead(pinNumber);
// };