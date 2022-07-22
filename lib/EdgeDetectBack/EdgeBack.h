#ifndef Edge_h
#define Edge_h

#include <Arduino.h>
#include <Motor.h>
#include <Constants.h>
#include <Helper.h>


class EdgeBack {
    public:

        /**
         * @brief Construct the BackEdge Detection
         * 
         * @param leftMotor 
         * @param rightMotor 
         * @param motorSpeed 
         */
        EdgeBack(Motor leftMotor,Motor rightMotor,int motorSpeed);

        /**
         * @brief Use BackEdge Detection
         * 
         */
        void useEdgeBack();

        /**
        * Setter and Getter Methods 
        * 
        */
        //int getBottomLeftSensorVal() { bottomLeftSensor = Helper:: getAverageAnalogValue(bottomLeftSensorPin, EdgeFollowerNS::NUM_READINGS); return bottomLeftSensor; }
        //int getBottomRightSensorVal() { bottomRightSensor = Helper:: getAverageAnalogValue(bottomRightSensorPin, EdgeFollowerNS:: NUM_READINGS); return bottomRightSensor; }

        int getBottomLeftSensorVal() { bottomLeftSensor = digitalRead(bottomLeftSensorPin); return bottomLeftSensor; }
        int getBottomRightSensorVal() { bottomRightSensor = digitalRead(bottomRightSensorPin); return bottomRightSensor; }

        /**
         * @brief Detect if sensor is on edge 
         * 
         * @param sensorValue 
         * @param highReading of 1
         * @return true 
         * @return false 
         */
        bool sensorOnEdge(int sensorValue, int highReading);

        /**
         * @brief Move straight for a certain time
         * 
         * @param leftMotorSpeed 
         * @param rightMotorSpeed 
         * @param moveTime 
         */
        void moveForCertainTime(int leftMotorSpeed, int rightMotorSpeed, Motor leftMotor, Motor rightMotor, int moveTime);


    private :

        //Motors
        Motor leftMotor;
        Motor rightMotor;
        
        int motorSpeed;

        //Sensors
        int bottomLeftSensor;
        int bottomRightSensor;

        //Sensor Pins
        int bottomLeftSensorPin;
        int bottomRightSensorPin;

        //Edge Threshold
        int threshold;

        //Number of Readings
        int numReadings;
};


#endif