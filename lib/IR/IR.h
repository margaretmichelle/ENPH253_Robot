// #ifndef IR_h
// #define IR_h
// #include <Arduino.h>
// #include <Constants.h>
// #include <Motor.h>
// #include <Helper.h>

// class IR {

// public:

//   /**
//    * Construct the PID
//    **/
//   IR(Motor leftMotor, Motor rightMotor, int motorSpeed);
  
//   /**
//    * Use IR
//    */
//   void followIR();

// private:

//   /**
//    * @param pinNumber analog pin used for IR sensor
//    * @return double, reading from IR sensor
//    */
//   double readIRSensor(int pinNumber);

//   int getLeftSensorVal() { leftIRReading = Helper:: getAverageAnalogValue(leftSensor, IRFollowerNS::NUM_READINGS); return leftIRReading; }
//   int getRightSensorVal() { rightIRReading = Helper:: getAverageAnalogValue(rightSensor, IRFollowerNS::NUM_READINGS); return rightIRReading; }
//   int getMiddleSensorVal() { middleIRReading = Helper:: getAverageAnalogValue(middleSensor, IRFollowerNS::NUM_READINGS); return middleIRReading; }

//   // Motors
//   Motor leftMotor;
//   Motor rightMotor;

//   // Motor Speeds
//   int motorSpeed;
//   int leftMotorSpeed;
//   int rightMotorSpeed;

//   // IR Sensors
//   int leftSensor;
//   int middleSensor;
//   int rightSensor;

//   // Readings
//   double leftIRReading;
//   double middleIRReading;
//   double rightIRReading;
  
//   // Timing
//   long lastReadTime;
//   long currentTimeUS;
// };

// #endif