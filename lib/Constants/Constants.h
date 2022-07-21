#ifndef Constants_h
#define Constants_h
#include <Arduino.h>
#include <Wire.h>

// these Pin numbers are not finalized, please verify before using

const int MAP_8_BIT_TO_12_BIT = 16;

namespace ClawNS {
  const int UP_ANGLE = 180;
  const int DOWN_ANGLE = 0;
  const int EWOK_MULTIPLIER = 3;
  const int COOLDOWN_TIME = 5000;  // 5 s

  namespace Left {
    const int UP_ANGLE = 0;
    const int DOWN_ANGLE = 180;
    const int CLOSED_ANGLE = 160;
    const int ARCHWAY_ANGLE = 70;
    const int OPEN_ANGLE = 40;
    //Temp Values
    const int SENSOR_PIN = PB11;
    const int DETACHED_SENSOR_PIN = PB10;
    const int OPEN_CLAW_SERVO = PA6;
    const int ORIENT_CLAW_SERVO = PA7;
    const int STARTING_ROTATION = 10;
  }
  namespace Right {
    const int UP_ANGLE = 180;
    const int DOWN_ANGLE = 0;
    const int CLOSED_ANGLE = 0;
    const int ARCHWAY_ANGLE = 30;
    const int OPEN_ANGLE = 110;
    const int SENSOR_PIN = PB14; //Confirmed for now
    const int OPEN_CLAW_SERVO = PA8; //CFN
    const int ORIENT_CLAW_SERVO = PA9; //CFN
    const int STARTING_ROTATION = 0;
  }
}

namespace GyroNS {
  
}

namespace IRNS {
  // pins
  const int CONTROL_PIN_1 = PA1;
  const int CONTROL_PIN_2 = PA0;
  const int ONE_KHZ_PIN = PB1;
  const int TEN_KHZ_PIN = PB0;

  // averaging
  const int NUM_READINGS = 1;
  const int NUM_QSD_AVERAGE = 5;

  // thresholds
  const int TEN_KHZ_THRESHOLD = 350;
  const int TEN_DIFF_THRESHOLD = 300;
  const int ONE_KHZ_THRESHOLD = 150;
}

/****** Bots ******/
namespace SlaveNS {
  const int MIN_ADVANCE_TIME = 500;
  // Pins
  const int LEFT_MOTOR_PIN_1 = PA9;
  const int LEFT_MOTOR_PIN_2 = PA10;
  const int RIGHT_MOTOR_PIN_1 = PB8;
  const int RIGHT_MOTOR_PIN_2 = PB9;

  const int ADVANCE_PIN = PB3;
  const int STOP_PIN = PB5;

  /* while tuning, use specified numbers
  // Speeds + Kps
  const int RAMP_CLIMBING_SPEED = 140;
  const int RAMP_CLIMBING_KP = 12;

  const int PRE_BRIDGE_SPEED = 60;
  const int PRE_BRIDGE_KP = 13;

  const int BRIDGE_CROSSING_SPEED = 85;
  const int BRIDGE_CROSSING_KP= 10;

  const int PRE_IR_SPEED = 80;
  const int PRE_IR_KP = 9;

  const int POST_IR_SPEED = 90;
  const int POST_IR_KP = 9;
  */
}

namespace MasterNS {
  // Temp Value

  // Pins
  const int LEFT_MOTOR_PIN_1 = PA_11;
  const int LEFT_MOTOR_PIN_2 = PA_10;
  const int RIGHT_MOTOR_PIN_1 = PB_8;
  const int RIGHT_MOTOR_PIN_2 = PB_9;

  const int ADVANCE_SLAVE_PIN = PB12;
  const int STOP_SLAVE_PIN = PB13;

  // Speeds
  const int STANDARD_MOTOR_SPEED = 80;
}

/****** PID ******/
namespace TapeFollowerNS {
  // Pins
  const int LEFT_FRONT_SENSOR_PIN = PB1;
  const int RIGHT_FRONT_SENSOR_PIN = PB0;

  // Error
  const int ONE_OFF_ERROR = 1;
  const int BOTH_OFF_ERROR = 3;

  // Readings
  const int WHITE_THRESHOLD = 300;
  const int NUM_READINGS = 1;
  const int SUMMED_ERROR_LIMIT = 0;

  // Gains
  const int KP = 15;
  const int KD = 2;
  const int KI = 0;
}

namespace EdgeFollowerNS {
  // Pins
  const int TOP_LEFT_SENSOR_PIN = PA0; //not the correct values right now 
  const int TOP_RIGHT_SENSOR_PIN = PA1;
  const int BOTTOM_LEFT_SENSOR_PIN = PA2;
  const int BOTTOM_RIGHT_SENSOR_PIN = PA3;
  const int LEFT_MOTOR_PIN_1 = 2;
  const int LEFT_MOTOR_PIN_2 = 4;
  const int RIGHT_MOTOR_PIN_1 = 3;
  const int RIGHT_MOTOR_PIN_2 = 5;

  //Move For a Certain Amount of Time;

  const int MOVE_FOR_TIME = 300;

  // Readings
  const int ONE_OFF_ERROR = 1;
  const int EDGE_THRESHOLD = 400;
  const int NUM_READINGS = 1;
  const int SUMMED_ERROR_LIMIT = 0;
  const int STANDARD_MOTOR_SPEED = 40;

  // Gains
  const int KP = 9;
  const int KD = 1;
  const int KI = 0;
}

namespace DriveMotorPins {

  const int BASE_SPEED = 80; 
  const int MOTOR_FREQ = 200;
}

namespace OLEDDisplayNS {
  // Pins
  const int BUTTON_PIN = PA9;
  const int CLK_PIN = PB14;
  const int DT_PIN = PB15;

  // OLED constants
  const int SCREEN_WIDTH = 128;
  const int SCREEN_HEIGHT = 64;
  const int OLED_RESET = -1;
}

namespace ClawConstants{
  const int CLAW_OPEN = 180;
  const int CLAW_CLOSED = 0;
}

namespace ArmConstants{
  const int ARM_UP = 180;
  const int ARM_DOWN = 0;
}

namespace HighAndLow {
  const int HIGH_READING = 1;
  const int LOW_READING = 0;
}

namespace ObstacleNS {; 
  // not sure what the threshold value is yet we need to test
  const int ECHO_PIN = PA4;
  const int TRIGPIN = PA5;
  const int MAX_DISTANCE = 30;
  const int MIN_DISTANCE = 50;
}

#endif
