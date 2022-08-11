#ifndef Constants_h
#define Constants_h
#include <Arduino.h>
#include <Wire.h>

/* Master Constants */

const int MAP_8_BIT_TO_12_BIT = 16;

namespace MasterNS {
  // Temp Value

  // Pins
  const int LEFT_MOTOR_PIN_1 = PA_9;
  const int LEFT_MOTOR_PIN_2 = PA_8;
  const int RIGHT_MOTOR_PIN_1 = PB_9;
  const int RIGHT_MOTOR_PIN_2 = PB_8;

  const int BP_COMM_IN = PB12;
  const int BP_COMM_OUT = PB13;

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
  const int BLACK_THRESHOLD = 600;
  const int NUM_READINGS = 1;
  const int SUMMED_ERROR_LIMIT = 0;

  // Gains
  const int KP = 60;
  const int KI = 0;
  const int KD = 5;
}

namespace EdgeFollowerNS {
  // Pins
  const int TOP_LEFT_SENSOR_PIN = PA6;
  const int TOP_RIGHT_SENSOR_PIN = PA7;
  const int BOTTOM_LEFT_SENSOR_PIN = PA5;
  const int BOTTOM_RIGHT_SENSOR_PIN = PA4;
  const int LEFT_MOTOR_PIN_1 = PA_8;
  const int LEFT_MOTOR_PIN_2 = PA_9;
  const int RIGHT_MOTOR_PIN_1 = PB_8;
  const int RIGHT_MOTOR_PIN_2 = PB_9;

  const int MOVE_FOR_TIME = 300;

  // Readings
  const int ONE_OFF_ERROR = 1;
  const int EDGE_THRESHOLD = 400;
  const int NUM_READINGS = 1;
  const int SUMMED_ERROR_LIMIT = 0;
  const int STANDARD_MOTOR_SPEED = 40;

  // Gains
  const int KP = 100;
  const int KI = 0;
  const int KD = 1;
}

namespace DriveMotorPins {

  const int BASE_SPEED = 80; 
  const int MOTOR_FREQ = 200;
}

namespace OLEDDisplayNS {
  // Pins
  const int BUTTON_PIN = PB3;
  const int CLK_PIN = PB15;
  const int DT_PIN = PB14;

  // OLED constants
  const int SCREEN_WIDTH = 128;
  const int SCREEN_HEIGHT = 64;
  const int OLED_RESET = -1;
}

namespace HighAndLow {
  const int HIGH_READING = 1;
  const int LOW_READING = 0;
}

namespace ObstacleNS {; 
  const int LEFT_TRIG_PIN = PA3; //left
  const int LEFT_ECHO_PIN = PA2;
  const int RIGHT_TRIG_PIN = PA1; //right 
  const int RIGHT_ECHO_PIN = PA0;
  const int DISTANCE_TO_IDOL = 30; //cm
  const int IDOL_ONE_ANGLE = 93;
  const int IDOL_TWO_ANGLE = 85;
}

namespace EncoderNS{
  const int RIGHT_ENCODER_CLK_PIN = PB11;
  const int LEFT_ENCODER_CLK_PIN = PB10;
  const int LEFT_ENCODER_DT_PIN = PB10;
  const int RIGHT_ENCODER_DT_PIN = PB11;
  const float WHEEL_DIA_MM = 88.9;
  const float ROTATION_DISTANCE_MM = WHEEL_DIA_MM * PI;
  const float PULSES_PER_ROTATION = 131.0*11.0*7.0/5.0;
  const float PULSES_PER_RAD = PULSES_PER_ROTATION/(2*PI);
  const float DISTANCE_PER_PULSE = ROTATION_DISTANCE_MM/PULSES_PER_ROTATION;
  const float ROT_KP = 0.000000005;
  const float ROT_KD =0;
  const float DIST_KP = 0.0000000001;
  const float DIST_KD = 0.0000000005;
  const int POWER_OFFSET = 5;
  const float CENTRE_TO_RIGHT_WHEEL_MM = 99.5;
  const float CENTRE_TO_LEFT_WHEEL_MM = 99.5;
  const int PIVOT_WHEEL_SPEED = 83;
  const float PIVOT_DIAMETER = 199;
  const float PIVOT_CIRCUMFERENCE = PIVOT_DIAMETER * PI;
}


/* Slave Constants */

namespace SlaveNS {
  const int MIN_ADVANCE_TIME = 500;
  const int BP_COMM_OUT = PB12;
  const int BP_COMM_IN = PB13;
}

namespace ArmNS {
  // Pins
  const int LEFT_ARM_SERVO_PIN = PB_6;
  const int RIGHT_ARM_SERVO_PIN = PB_7;
  const int LEFT_HALL_EFFECT_SENSOR_PIN = PA5;
  const int RIGHT_HALL_EFFECT_SENSOR_PIN = PA4;

  // Constants
  const int LEFT_ARM_UP = 110;
  const int LEFT_ARM_DOWN = 0;
  const int LEFT_ARM_DROP = 180;
  const int LEFT_ARM_ARCH = 160;
  const int RIGHT_ARM_UP = 35;
  const int RIGHT_ARM_DOWN = 160;
  const int RIGHT_ARM_DROP = 0;
  const int RIGHT_ARM_ARCH = 0;
}

namespace ClawNS {
  // Pins
  const int LEFT_CLAW_SERVO_PIN = PA_8;
  const int RIGHT_CLAW_SERVO_PIN = PA_9;

  // Constants
  const int LEFT_CLAW_OPEN = 180;
  const int LEFT_CLAW_CLOSED = 0;
  const int RIGHT_CLAW_OPEN = 0;
  const int RIGHT_CLAW_CLOSED = 180;
  const int CLAW_PARTIAL_CLOSE = 70;
}

namespace BridgeDeployNS {
  // edge
  const int EDGE_THRESHOLD = 350;
  const int NUM_READINGS = 2;
  const int EDGE_ALIGN_SPEED = 110;

  const int SERVO_REST_ANGLE = 0;
  const int UNHOOK_SERVO_FINAL_ANGLE = 120;

  namespace UnHookBridge {
    const int UNHOOK_BRIDGE_SERVO_PIN = PA_0;
  }
}

namespace ServoNS {
  const int SERVO_FREQ = 100;
  const int MAX_PULSE_WIDTH = 2500;
  const int MIN_PULSE_WIDTH = 500;
}

namespace ZiplineNS {
  const int ZIPLINE_MOTOR_PIN_1 = PB_1;
  const int ZIPLINE_MOTOR_PIN_2 = PB_0;
  const int ZIPLINE_SPEED_LIFT = 60;
  const int ZIPLINE_OPERATION_TIME = 1000;
}

#endif
