#ifndef BridgeLay_h
#define BridgeLay_h

#include <Constants.h>
#include <Helper.h>
#include <Motor.h>
#include <ServoMotor.h>

class BridgeDeploy {
public:

  /**
   * Constructor
   */
  BridgeDeploy(Motor leftMotor, Motor rightMotor);

  /**
   * @brief deploy bridge. Puts servos both in bridge release angle, then puts them back
   */
  void deployBridge();
  
  /** 
   * @brief Align with edge. Stops robot when complete
   */
  void edgeAlign();

  /**
   * @brief Updates edge states. Return true if both sensors are on edge, else false
   *
   * @return true if both sensors on edge, else false
   */
  bool bothOnEdge();

  /**
   * @brief Updates edge states. Return true if either sensor is on edge, else false
   *
   * @return bool true if either sensors on edge, else false
   */
  bool onEdge();
  
  /* getters */
  /**
   * update sensors and return the value 
   */
  int getLeftSensor() { leftSensor = Helper::getAverageAnalogValue(EdgeFollowerNS::TOP_LEFT_SENSOR_PIN, BridgeDeployNS::NUM_READINGS); return leftSensor; }
  int getRightSensor() { rightSensor = Helper::getAverageAnalogValue(EdgeFollowerNS::TOP_RIGHT_SENSOR_PIN, BridgeDeployNS::NUM_READINGS); return rightSensor; }

  int getLeftMotorSpeed() { return leftMotorSpeed; }
  int getRightMotorSpeed() { return rightMotorSpeed; }

private:

  // Motors + servos
  Motor leftMotor;
  Motor rightMotor;
  ServoMotor unHookServo;
  ServoMotor pushServo;

  // Sensors
  int leftSensor;
  int rightSensor;
  int leftMotorSpeed;
  int rightMotorSpeed;

  // Edge State
  bool leftOnEdge;
  bool rightOnEdge;

};

#endif