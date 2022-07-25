#include <Arduino.h>
#include <Constants.h>
#include <Helper.h>
#include <Motor.h>
#include <PID.h>
#include <OLED.h>

// Constructor
PID::PID(PIDType pidType, Motor leftMotor, Motor rightMotor, int motorSpeed) : pidType(pidType),
                                                                               lastError(0),
                                                                               summedError(0),
                                                                               lastDifferentError(0),
                                                                               leftMotor(leftMotor),
                                                                               rightMotor(rightMotor),
                                                                               motorSpeed(motorSpeed)
{
  switch (pidType)
  {
    case PIDType ::TapeFollower:
    {
      leftSensorPin = TapeFollowerNS::LEFT_FRONT_SENSOR_PIN;
      rightSensorPin = TapeFollowerNS::RIGHT_FRONT_SENSOR_PIN;
      summedErrorLimit = TapeFollowerNS::SUMMED_ERROR_LIMIT;
      threshold = TapeFollowerNS::WHITE_THRESHOLD;
      numReadings = TapeFollowerNS::NUM_READINGS;

      pinMode(leftSensorPin, INPUT_PULLUP);
      pinMode(rightSensorPin, INPUT_PULLUP);
      break;
    }
    case PIDType::EdgeFollower: 
    {
      topLeftSensorPin = EdgeFollowerNS::TOP_LEFT_SENSOR_PIN;
      topRightSensorPin = EdgeFollowerNS::TOP_RIGHT_SENSOR_PIN;
      summedErrorLimit = EdgeFollowerNS::SUMMED_ERROR_LIMIT;
      threshold = HighAndLow::HIGH_READING;
      numReadings = EdgeFollowerNS::NUM_READINGS;

      pinMode(topRightSensorPin,INPUT_PULLUP);
      pinMode(topLeftSensorPin, INPUT_PULLUP);
      break;
    }
    default:
    {
      // Error never should be here should always have PIDType
      break;
    }
  }
  
}

void PID::usePID(int KP, int KI, int KD)
{
  //Reflectance Tape and Edge Top Error 
  int error;

  int errorBottom;

  switch (pidType) {
    case PIDType::TapeFollower:
    {
      // average QRD values for Tape
      getLeftSensorVal();
      getRightSensorVal();

      bool leftOnWhite = sensorOnWhite(leftSensor, threshold);
      bool rightOnWhite = sensorOnWhite(rightSensor, threshold);
      error = getTapeError(leftOnWhite, rightOnWhite, TapeFollowerNS::ONE_OFF_ERROR, TapeFollowerNS::BOTH_OFF_ERROR);
      break;
    }
    case PIDType::EdgeFollower:
    {
      // get average QRD values for the edge 
      getTopLeftSensorVal();
      getTopRightSensorVal();

      bool topLeftOnPlatform = !sensorOnEdge(topLeftSensor, threshold);
      bool topRightOnPlatform = !sensorOnEdge(topRightSensor, threshold);
      error = getEdgeError(topLeftOnPlatform, topRightOnPlatform, EdgeFollowerNS::ONE_OFF_ERROR);
      break;
    }
  }

  summedError = getSummedError(error, summedError, summedErrorLimit);

  double derivativeError;

  if (lastError != error) {
    derivativeError = (error - lastError) / (micros() - lastTime);
    lastDifferentError = error;
    timeOfLastChange = lastTime;
  }

  else
    derivativeError = (error - lastError) / (micros() - timeOfLastChange); // will be 0 anyways

  // reset last values
  lastError = error;
  lastTime = micros();

  // set new motor speeds
  double adjustment = (KP * error) + (KI * summedError) + (KD * derivativeError);
  leftMotorSpeed = motorSpeed - adjustment;
  rightMotorSpeed = motorSpeed + adjustment;
  leftMotor.speed(leftMotorSpeed);
  rightMotor.speed(rightMotorSpeed);
}

bool PID::sensorOnWhite(int sensorValue, int threshold)
{
  if (sensorValue < threshold)
  {
    return true;
  }
  return false;
}

bool PID::bothOnBlack(int threshold) {
    getLeftSensorVal();
    getRightSensorVal();

    if(leftSensor > threshold && rightSensor > threshold) {
      return true;
    }
    return false;
}

int PID::getTapeError(bool leftOnWhite, bool rightOnWhite, int oneOffError, int bothOffError)
{
  // ensure correct input
  if (pidType != PIDType::TapeFollower)
  {
  } // THROW EXCEPTION

  int error = lastError;

  // if both sensors are on white, set error based on lastError
  if (leftOnWhite && rightOnWhite)
  {
    if (lastError > 0)
    {
      error = bothOffError;
    }
    else if (lastError < 0)
    {
      error = -bothOffError;
    }
    // if suddenly went off tape) dont need
  }

  // set error left or right
  else if (rightOnWhite)
  {
    error = oneOffError;
  }
  else if (leftOnWhite)
  {
    error = -oneOffError;
  }

  else
  {
    error = 0;
  }

  return error;
}

int PID::getEdgeError(bool correctLeftPosition, bool correctRightPosition, int oneOffError) {
  // ensure correct input
  if (pidType != PIDType::EdgeFollower){}  // THROW EXCEPTION

  int error = 0;

  // set error left or right
  if (!correctRightPosition) { error = -oneOffError; }
  else if (!correctLeftPosition) { error = oneOffError; }
  else { error = 0; }

  return error;
}

bool PID::sensorOnEdge(int sensorValue, int highReading) {
    if(sensorValue == highReading) { //we get a high reading when on an edge 
        return true;
    }
    else {
        return false;
    }
}

int PID::getSummedError(int error, int lastSummedError, int summedErrorLimit)
{ // there integral term KI = 0 so we will need to change summedErrorLimit and KI to stabilize robot
  // get absolute value of summedErrorLimit
  if (summedErrorLimit < 0)
  {
    summedErrorLimit = -summedErrorLimit;
  }

  int summedError = lastSummedError + error;

  // anti-windup
  if (summedError > summedErrorLimit)
  {
    summedError = summedErrorLimit;
  }
  else if (summedError < -summedErrorLimit)
  {
    summedError = -summedErrorLimit;
  }

  return summedError;
}
