#include <Constants.h>
#include <Helper.h>

#include <Bridge.h>
#include <ServoMotor.h>

BridgeDeploy::BridgeDeploy(Motor leftMotor, Motor rightMotor) :
  leftMotor(leftMotor),
  rightMotor(rightMotor),
  leftOnEdge(false),
  rightOnEdge(false)
  {

  }
  

bool BridgeDeploy::bothOnEdge() {
  leftOnEdge = getLeftSensor() > BridgeDeployNS::EDGE_THRESHOLD; //use Top left and right edge sensing pins
  rightOnEdge = getRightSensor() > BridgeDeployNS::EDGE_THRESHOLD;

  return (leftOnEdge && rightOnEdge);
}

bool BridgeDeploy::onEdge() {
  leftOnEdge = getLeftSensor() > BridgeDeployNS::EDGE_THRESHOLD;
  rightOnEdge = getRightSensor() > BridgeDeployNS::EDGE_THRESHOLD;

  return (leftOnEdge || rightOnEdge);
}

void BridgeDeploy::edgeAlign() {
  while(!bothOnEdge()) {
    // left on edge => turn right wheel more
    if (leftOnEdge) {
      leftMotor.speed(-BridgeDeployNS::EDGE_ALIGN_SPEED); 
      rightMotor.speed(BridgeDeployNS::EDGE_ALIGN_SPEED);
    }

    // right on edge => turn left wheel more
    else if (rightOnEdge) {
      leftMotor.speed(BridgeDeployNS::EDGE_ALIGN_SPEED); 
      rightMotor.speed(-BridgeDeployNS::EDGE_ALIGN_SPEED);
    }

    // if neither on edge, then go straight till it finds edge
    else { 
      leftMotor.speed(BridgeDeployNS::EDGE_ALIGN_SPEED); 
      rightMotor.speed(BridgeDeployNS::EDGE_ALIGN_SPEED);
    }
  }

  // when both on edge, stop
  leftMotor.stop();
  rightMotor.stop();
  delay(500);
}



