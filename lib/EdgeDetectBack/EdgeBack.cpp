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
        moveForCertainTime(80,80,leftMotor,rightMotor,EdgeFollowerNS::MOVE_FOR_TIME); //go straight since both off i think moving for 300 milliseconds would be good??
    }
    else if(!leftOnPlatform && rightOnPlatform) {
        moveForCertainTime(80,100,leftMotor,rightMotor,EdgeFollowerNS::MOVE_FOR_TIME); //turn right if left is not on platform 
    }
    else if(leftOnPlatform && !rightOnPlatform) {
        moveForCertainTime(100,80,leftMotor,rightMotor,EdgeFollowerNS::MOVE_FOR_TIME); //turn left if right is not on platform
    }
    else {
        //do nothing if both are on platform
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

void moveForCertainTime(int leftMotorSpeed, int rightMotorSpeed, Motor leftMotor, Motor rightMotor, int timeToMove) {
    leftMotor.speed(leftMotorSpeed);
    rightMotor.speed(rightMotorSpeed);
    delay(timeToMove);
}

