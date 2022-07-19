#include <EdgeBack.h>
#include <Motor.h>
#include <Constants.h>
#include <Arduino.h>

EdgeBack :: EdgeBack (Motor leftMotor,Motor rightMotor, int motorSpeed) : 
    leftMotor(leftMotor),
    rightMotor(rightMotor),
    motorSpeed(motorSpeed)
    {
      bottomLeftSensorPin = EdgeFollowerNS::TOP_LEFT_SENSOR_PIN;
      bottomRightSensorPin = EdgeFollowerNS::TOP_RIGHT_SENSOR_PIN;
      threshold = EdgeFollowerNS::EDGE_THRESHOLD;
      numReadings = EdgeFollowerNS::NUM_READINGS;

      //Set-up pins.  Motor pins are handled by library
      pinMode(bottomLeftSensorPin, INPUT_PULLUP);
      pinMode(bottomRightSensorPin, INPUT_PULLUP);
    }

void EdgeBack::useEdgeBack() {

    //Get average QRD Values on back
    getBottomLeftSensorVal();
    getBottomRightSensorVal();

    //Get 
    bool leftOnPlatform = !sensorOnEdge(bottomLeftSensor,threshold);
    bool rightOnPlatform = !sensorOnEdge(bottomRightSensor,threshold);

    if(!leftOnPlatform && !rightOnPlatform) {
        moveForCertainTime()
    }


}    

bool sensorOnEdge(int sensorValue, int edgeThreshold) {
    if(sensorValue > edgeThreshold) {
        return true;
    }
    else {
        return false;
    }
}

void moveForCertainTime(int leftMotorSpeed, int rightMotorSpeed, int timeToMove) {

}

