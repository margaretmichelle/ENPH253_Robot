#include <EdgeBack.h>
#include <Motor.h>
#include <Constants.h>
#include <Arduino.h> //To do:  Add interrupts 

EdgeBack :: EdgeBack (Motor leftMotor,Motor rightMotor, int motorSpeed) : 
    leftMotor(leftMotor),
    rightMotor(rightMotor),
    motorSpeed(motorSpeed)
    {
      bottomLeftSensorPin = EdgeFollowerNS::BOTTOM_LEFT_SENSOR_PIN;
      bottomRightSensorPin = EdgeFollowerNS::BOTTOM_RIGHT_SENSOR_PIN;
      topLeftSensorPin = EdgeFollowerNS::TOP_LEFT_SENSOR_PIN;
      topRightSensorPin = EdgeFollowerNS::TOP_RIGHT_SENSOR_PIN;
      
      //threshold = EdgeFollowerNS::EDGE_THRESHOLD; we are using digital readings 1 and 0
      //numReadings = EdgeFollowerNS::NUM_READINGS;

      //Set-up pins.  Motor pins are handled by library
      pinMode(bottomLeftSensorPin, INPUT_PULLUP);
      pinMode(bottomRightSensorPin, INPUT_PULLUP);
      pinMode(topRightSensorPin,INPUT_PULLUP);
      pinMode(topLeftSensorPin, INPUT_PULLUP);
    }

void EdgeBack::useEdge() {

    //Get digital QRD Values High and Low 
    getBottomLeftSensorVal();
    getBottomRightSensorVal();
    getTopLeftSensorVal();
    getTopRightSensorVal();

    //Get 
    bool topLeftOnPlatform = !sensorOnEdge(topLeftSensor,HighAndLow::HIGH_READING);
    bool topRightOnPlatform = !sensorOnEdge(topRightSensor,HighAndLow::HIGH_READING);
    //Get 
    bool bottomLeftOnPlatform = !sensorOnEdge(bottomLeftSensor,HighAndLow::HIGH_READING);
    bool bottomRightOnPlatform = !sensorOnEdge(bottomRightSensor,HighAndLow::HIGH_READING);

    if (!topLeftOnPlatform && !topRightOnPlatform && bottomLeftOnPlatform && bottomRightOnPlatform) {
        moveForCertainTime(-80,-80,leftMotor,rightMotor,EdgeFollowerNS::MOVE_FOR_TIME); //go straight since both off i think moving for 300 milliseconds would be good??
    } else if (!topLeftOnPlatform && topRightOnPlatform && bottomLeftOnPlatform && bottomRightOnPlatform) {
        moveForCertainTime(90,60,leftMotor,rightMotor,EdgeFollowerNS::MOVE_FOR_TIME); //turn right if left is not on platform 
    } else if (topLeftOnPlatform && !topRightOnPlatform && bottomLeftOnPlatform && bottomRightOnPlatform) {
        moveForCertainTime(60,90,leftMotor,rightMotor,EdgeFollowerNS::MOVE_FOR_TIME); //turn left if right is not on platform
    } else if (topLeftOnPlatform && topRightOnPlatform && !bottomLeftOnPlatform && !bottomRightOnPlatform) {
        moveForCertainTime(80,80,leftMotor,rightMotor,EdgeFollowerNS::MOVE_FOR_TIME);
    } else if (topLeftOnPlatform && topRightOnPlatform && !bottomLeftOnPlatform && bottomRightOnPlatform) {
        moveForCertainTime(90,60,leftMotor,rightMotor,EdgeFollowerNS::MOVE_FOR_TIME);
    } else if (topLeftOnPlatform && topRightOnPlatform && bottomLeftOnPlatform && !bottomRightOnPlatform) {
        moveForCertainTime(60,90,leftMotor,rightMotor,EdgeFollowerNS::MOVE_FOR_TIME);
    }
    else {
        //do nothing if both are on platform
    }
}

bool EdgeBack::sensorOnEdge(int sensorValue, int highReading) {
    if (sensorValue == highReading) { //we get a high reading when on an edge 
        return true;
    } else {
        return false;
    }
}

void EdgeBack::moveForCertainTime(int leftMotorSpeed, int rightMotorSpeed, Motor leftMotor, Motor rightMotor, int timeToMove) {
    leftMotor.speed(leftMotorSpeed);
    rightMotor.speed(rightMotorSpeed);
    delay(timeToMove);

    leftMotor.stop();
    rightMotor.stop();
}

