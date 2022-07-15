#include <Arduino.h>
#include <Constants.h>
#include <Helper.h>
#include <Motor.h>
#include <PID.h>
#include <OLED.h>

//Constructor
PID::PID(PIDType pidType, Motor leftMotor, Motor rightMotor, int motorSpeed) :
  pidType(pidType),
  lastError(0),
  summedError(0),
  lastDifferentError(0),
  leftMotor(leftMotor),
  rightMotor(rightMotor),
  motorSpeed(motorSpeed)
  {
    switch(pidType) {
      case PIDType :: TapeFollower : {
        leftSensorPin = TapeFollowerNS::LEFT_FRONT_SENSOR_PIN;
        rightSensorPin = TapeFollowerNS::RIGHT_FRONT_SENSOR_PIN;
        summedErrorLimit = TapeFollowerNS::SUMMED_ERROR_LIMIT;
        threshold = TapeFollowerNS::WHITE_THRESHOLD;
        numReadings = TapeFollowerNS::NUM_READINGS;
        break;
      }
      default : {
        //Error never should be here should always have PIDType 
      }
    }

  //Setup Pins.  Motor pins are handled by library
  pinMode(leftSensorPin, INPUT_PULLUP);
  pinMode(rightSensorPin, INPUT_PULLUP);
}

void PID:: usePID(OLED oled) {

//get average QRD values
getLeftSensorVal();
getRightSensorVal();

// print qrd values
Serial.print("TL: "); Serial.print(leftSensor); Serial.print(" TR: "); Serial.println(rightSensor);

int error;

switch(pidType) {
  case PIDType::TapeFollower: {
    bool leftOnWhite =  sensorOnWhite(leftSensor,threshold);
    bool rightOnWhite = sensorOnWhite(rightSensor, threshold);
    error = getTapeError(leftOnWhite,rightOnWhite,TapeFollowerNS::ONE_OFF_ERROR, TapeFollowerNS::BOTH_OFF_ERROR);
    break;
  }
}

summedError = getSummedError(error,summedError,summedErrorLimit);

double derivativeError;

if(lastError!=error) {
  derivativeError = (error - lastError) / (micros() - lastTime);
  lastDifferentError = error;
  timeOfLastChange = lastTime;
}

else derivativeError = (error - lastError) / (micros() - timeOfLastChange); // will be 0 anyways 

//reset last values
lastError = error;
lastTime = micros();

// set new motor speeds
double adjustment = (oled.getKD() * error) + (oled.getKI() * summedError) + (oled.getKD() * derivativeError);
leftMotorSpeed = motorSpeed - adjustment;
rightMotorSpeed = motorSpeed + adjustment;
Serial.print("L"); Serial.println(leftMotorSpeed);
Serial.print("R"); Serial.println(rightMotorSpeed);
leftMotor.speed(leftMotorSpeed);
rightMotor.speed(rightMotorSpeed);
}

bool PID:: sensorOnWhite(int sensorValue, int threshold) {
  if(sensorValue < threshold) { return true; }
  return false;
}

int PID::getTapeError(bool leftOnWhite, bool rightOnWhite, int oneOffError, int bothOffError) {
    // ensure correct input
  if (pidType != PIDType::TapeFollower) {}  // THROW EXCEPTION

  int error = lastError;

  // if both sensors are on white, set error based on lastError
  if (leftOnWhite && rightOnWhite) {
    if (lastError > 0) { error = bothOffError; }
    else if (lastError < 0) { error = -bothOffError; }
    // if suddenly went off tape) dont need 
  }

  // set error left or right
  else if (rightOnWhite) { error = oneOffError; }
  else if (leftOnWhite) { error = -oneOffError; }

  else { error = 0; }

  return error;
}

int PID::getSummedError(int error, int lastSummedError, int summedErrorLimit) { //there integral term KI = 0 so we will need to change summedErrorLimit and KI to stabilize robot 
  // get absolute value of summedErrorLimit
  if (summedErrorLimit < 0) { summedErrorLimit = -summedErrorLimit; }

  int summedError = lastSummedError + error;

  // anti-windup
  if (summedError > summedErrorLimit) { summedError = summedErrorLimit; }
  else if (summedError < -summedErrorLimit) { summedError = -summedErrorLimit; }

  return summedError;
}