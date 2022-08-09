#ifndef Robot_h
#define Robot_h
#include <Arduino.h>

#include <Constants.h>
#include <Helper.h>
#include <Motor.h>
#include <PID.h>
#include <OLED.h>
#include <Obstacle.h>
#include <EdgeBack.h>
#include <Arm.h>
#include <Claw.h>
#include <Bridge.h>
#include <Encoder.h>
#include <BridgeServo.h>


namespace Robot {

  /* States */
  enum class MasterState {
    Inactive,
    TapeFollow,
    IRRegion,
    ObstacleFollow, 
    EdgeFollow,
    Done,
    JustTape,
    TestServos,
    PositionandPickUpObject,
    Bridge,
    JustEdge,
    UpToArch,
    Random
  };
  enum class SlaveState {
    Inactive,
    ClawActivateIdolOne,
    ClawActivateIdolTwo,
    ClawActivateIdolThree,
    ClawActivateIdolFour,
    BridgeDeploy,
    ClawActivateIdolFive,
    ClawActivateIdolSix,
    ZiplineLift,
    Done
  };

  /* Bots */
  class Master {
    public:
      Master():
        leftMotor(MasterNS::LEFT_MOTOR_PIN_1, MasterNS::LEFT_MOTOR_PIN_2),
        rightMotor(MasterNS::RIGHT_MOTOR_PIN_1, MasterNS::RIGHT_MOTOR_PIN_2),
        tapeFollow(PIDType::TapeFollower, leftMotor, rightMotor, 200),
        edgeFollow(PIDType::EdgeFollower, leftMotor, rightMotor, 200),
        leftUltrasonic(ObstacleNS::LEFT_TRIG_PIN,ObstacleNS::LEFT_ECHO_PIN),
        rightUltrasonic(ObstacleNS::RIGHT_TRIG_PIN, ObstacleNS::RIGHT_ECHO_PIN),
        edgeBack(leftMotor,rightMotor,200),
        bridge(leftMotor,rightMotor),
        encoder(),
        state(MasterState::Inactive)
        {
          //Set-up Communication Pins
          pinMode(MasterNS::BP_COMM_IN, INPUT);
          pinMode(MasterNS::BP_COMM_OUT, OUTPUT);
          digitalWrite(MasterNS::BP_COMM_OUT, LOW);
        }
        

      /*
      @brief Returns current state of robot and performs action for one loop.
      */
      MasterState poll(OLED o);

      /**
       * @brief Set the state of the master. ONLY FOR DEBUGGING. Do not use on competition day
       */
      void setState(MasterState state) { this->state = state; }
      
      /**
       * @brief Use edge detection
       * 
       */
      void useEdgeDetection();

      void changeSlaveState();

    private:

      volatile bool slaveBusy = false;
      
      /*
      @brief Increase the master state

      @returns true if successful, false if unsuccessful (out of states)
      */
      bool incrementState();

      /**
       * @brief Tell secondary blue pill to start and wait until it has completed its task
       * 
       */
      void sendSlaveSignalandWait();

      /**
       * @brief stop motors
       * 
       */
      void stop();

      /**
       * @brief move for a certain amount of time (in milliseconds)
       * 
       * @param leftMotorSpeed 
       * @param rightMotorSpeed 
       * @param moveForTime 
       */
      void moveForCertainTime(int leftMotorSpeed, int rightMotorSpeed, int moveForTime);

      /**
       * @brief "shuffles" robot over towards detected object on the right side
       */
      void shuffleRight();

      void moveToObjectOnRight();
      void moveToObjectOnLeft();

      Motor leftMotor;
      Motor rightMotor;
      PID tapeFollow;
      PID edgeFollow;

      Obstacle leftUltrasonic;
      Obstacle rightUltrasonic;
      EdgeBack edgeBack;

      BridgeDeploy bridge;
      
      Encoder encoder;

      int countIdolPickUp = 0;

      bool stopped;

      OLED o;

      MasterState state;
  };

  class Slave {
    public:
        Slave(): 
        leftClaw(ClawNS::LEFT_CLAW_SERVO_PIN, ClawNS::LEFT_CLAW_OPEN, ClawNS::LEFT_CLAW_CLOSED),
        rightClaw(ClawNS::RIGHT_CLAW_SERVO_PIN, ClawNS::RIGHT_CLAW_OPEN, ClawNS::RIGHT_CLAW_CLOSED),
        leftArm(ArmNS::LEFT_ARM_SERVO_PIN, leftClaw, ArmNS::LEFT_HALL_EFFECT_SENSOR_PIN, ArmNS::LEFT_ARM_UP, ArmNS::LEFT_ARM_DOWN),
        rightArm(ArmNS::RIGHT_ARM_SERVO_PIN, rightClaw, ArmNS::RIGHT_HALL_EFFECT_SENSOR_PIN, ArmNS::RIGHT_ARM_UP, ArmNS::RIGHT_ARM_DOWN),
        bridgeServo(),
          //Put Constructors for Claw and zipline 
        state(SlaveState::Inactive) { 
          pinMode(SlaveNS::BP_COMM_IN, INPUT);
          pinMode(SlaveNS::BP_COMM_OUT, OUTPUT);
          digitalWrite(SlaveNS::BP_COMM_OUT, LOW);
        }

        /*
        @brief Returns current state of robot and performs action for one loop.
        */
        SlaveState poll();
        /**
         * @brief Set the state of master. ONLY FOR DEBUGGING. Do not use on competition day
         */
        void setState(SlaveState state) { this->state = state; }

        
    private:
        SlaveState state;
        bool stopped;
        void stop();

        Claw leftClaw;
        Claw rightClaw;
        Arm leftArm;
        Arm rightArm;

        BridgeServos bridgeServo;

        
        /*
        @brief Advances the big bot state

        @returns true if successful, false if unsuccessful (end of list)
        */
        bool advanceState();
    };
} // namespace Robot

#endif
