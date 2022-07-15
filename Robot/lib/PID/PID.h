#ifndef PID_h
#define PID_h
#include <Arduino.h>
#include <Constants.h>
#include <Helper.h>
#include <Motor.h>

enum class PIDType {
  TapeFollower,
  EdgeFollower
};

class PID {

public:

  /**
   * Construct the PID
   **/
  PID(PIDType pidType, Motor leftMotor, Motor rightMotor, int motorSpeed);

  /**
   * Use PID
   **/
  void usePID();

  /**
   * Reset PID (remove all stored error values)
   */
  void reset();

  /**
   * Set direction that robot will turn when lost (suddenly both off course)
   *
   * @param direction to turn (left or right)
   */
  void setLostTurningDirection(Side direction) { lostTurningDirection = direction; }

  /**
   * Check if both on white
   * 
   * @param leftSensor left value
   * 
   * @param rightSensor right value
   * 
   * @return true if both on white, else false
   */
  bool bothOnWhite(int leftSensor, int rightSensor);

  /**
   * Refind tape
   *
   * @param leftMotorSpeed left speed
   * 
   * @param rightMotorSpeed right speed
   * 
   * @param maxTime to try (in ms)
   * 
   * @return true if on tape, false if hits maxTime
   */
  bool refindTape(int leftMotorSpeed, int rightMotorSpeed, int maxTime);
  
  /**
   * Setter and getter methods
   **/
  void setKP(int KP) { this -> KP = KP; }
  void setKI(int KI) { this -> KI = KI; }
  void setKD(int KD) { this -> KD = KD; }

  int getKP() { return KP; }
  int getKI() { return KI; }
  int getKD() { return KD; }

  void setMotorSpeed(int motorSpeed) { this -> motorSpeed = motorSpeed; }
  int getRightMotorSpeed() { return rightMotorSpeed; }
  int getLeftMotorSpeed() { return leftMotorSpeed; }

  int getLeftSensorVal() { leftSensor = Helper:: getAverageAnalogValue(leftSensorPin, TapeFollowerNS::NUM_READINGS); return leftSensor; }
  int getRightSensorVal() { rightSensor = Helper:: getAverageAnalogValue(rightSensorPin, TapeFollowerNS::NUM_READINGS); return rightSensor; }

  void setThreshold(int threshold) { this->threshold = threshold; }
  int getThreshold() { return threshold; }


private:

  /**
   * Get average sensor readings value from analogPin
   * Average over numReadings samples
   *
   * \param analogPin analog pin number for reading
   * \param numReadings number of readings for average (must be >0)
   *
   * \return int which is the average sensor value
   **/
  int getAverageSensorValue(int analogPin, int numReadings);

  /**
   * Check if sensor is on white paint
   *
   * \param sensorValue QRD sensor value
   * \param whiteThreshold maximum white Threshold value
   *
   * \return bool true if sensor is on white, else returns false (returns true if sensorValue < whiteThreshold)
   **/
  bool sensorOnWhite(int sensorValue, int whiteThreshold);

  /**
   * Check if sensor is on edge
   *
   * \param sensorValue QRD sensor value
   * \param edgeThreshold minimum edge Threshold value
   *
   * \return bool true if sensor is on edge, else returns false (returns true if sensorValue > edgeThreshold)
   **/
  bool sensorOnEdge(int sensorValue, int edgeThreshold);

  /**
   * set tape error based on left and right sensor digital data and last error
   *
   * \param leftOnWhite is the left sensor on white?
   * \param rightOnWhite is the left sensor on white?
   * \param oneOffError error from one sensor being off tape
   * \param bothOffError error from both sensors being off tape
   *
   * \return int new error
   * \throws exception if this isn't tape follower
   **/
  int getTapeError(bool leftOnWhite, bool rightOnWhite, int oneOffError, int bothOffError);

  /**
   * set edge error based on left and right sensor digital data and last error
   *
   * \param leftOnEdge is the left sensor on edge?
   * \param rightOnEdge is the left sensor on edge?
   * \param oneOffError error from one sensor being on edge
   *
   * \return int new error
   * \throws exception both params are true OR this isn't edge avoider
   **/
  int getEdgeError(bool leftOnEdge, bool rightOnEdge, int oneOffError);

  /**
   * recalculate summed error, accounting for anti-windup
   *
   * \param error error in this loop
   * \param lastSummedError summed error from previous loop
   * \param summedErrorLimit anti-windup limit
   *
   * \return int new summedError
   **/
  int getSummedError(int error, int lastSummedError, int summedErrorLimit);

  // Pins
  int leftSensorPin;
  int rightSensorPin;

  PIDType pidType;

  // Gains
  int KP;
  int KD;
  int KI;

  // Error
  int lastError;
  int summedError;
  int lastDifferentError;

  // Times
  double lastTime;
  double timeOfLastChange;

  // Motors
  Motor leftMotor;
  Motor rightMotor;

  int leftMotorSpeed;
  int rightMotorSpeed;

  int leftSensor;
  int rightSensor;

  int threshold;
  int motorSpeed;
  int numReadings;
  int summedErrorLimit;

  Side lostTurningDirection;
};

#endif
