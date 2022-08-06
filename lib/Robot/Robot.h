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

namespace Robot {

  /* States */
  enum class MasterState {
    Inactive,
    TapeFollow,
    IRFollow,
    ObstacleFollow, 
    EdgeFollow,
    Done,
    JustTape,
    PickUpObject,
    PositionObject,
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
        tapeFollow(PIDType::TapeFollower, leftMotor, rightMotor, 110),
        edgeFollow(PIDType::EdgeFollower, leftMotor, rightMotor, 80),
        rightForwardUltrasonic(ObstacleNS::FORWARD_TRIG_PIN,ObstacleNS::FORWARD_ECHO_PIN),
        rightMidUltrasonic(ObstacleNS::FORWARD_TRIG_PIN, ObstacleNS::MID_ECHO_PIN),
        edgeBack(leftMotor,rightMotor,80),
        leftClaw(ClawNS::LEFT_CLAW_SERVO_PIN, ClawNS::LEFT_CLAW_OPEN, ClawNS::RIGHT_CLAW_CLOSED),
        rightClaw(ClawNS::RIGHT_CLAW_SERVO_PIN, ClawNS::RIGHT_CLAW_OPEN, ClawNS::RIGHT_CLAW_CLOSED),
        leftArm(ArmNS::LEFT_ARM_SERVO_PIN, leftClaw, ArmNS::LEFT_HALL_EFFECT_SENSOR_PIN, ArmNS::LEFT_ARM_UP, ArmNS::LEFT_ARM_DOWN),
        rightArm(ArmNS::RIGHT_ARM_SERVO_PIN, rightClaw, ArmNS::RIGHT_HALL_EFFECT_SENSOR_PIN, ArmNS::RIGHT_ARM_UP, ArmNS::RIGHT_ARM_DOWN),
        bridge(leftMotor,rightMotor),
        state(MasterState::Inactive)
        {
          //Set-up Communication Pins
          pinMode(MasterNS::ADVANCE_SLAVE_PIN, OUTPUT);
          pinMode(MasterNS::STOP_SLAVE_PIN, OUTPUT);
          digitalWrite(MasterNS::ADVANCE_SLAVE_PIN, LOW);
          digitalWrite(MasterNS::STOP_SLAVE_PIN, LOW);
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

      bool slaveBusy = false;
      
      /*
      @brief Increase the master state

      @returns true if successful, false if unsuccessful (out of states)
      */
      bool incrementState();

      /*
      @brief Advances the slave state

      */
      void signalSlaveAdvance();

      /*
      @brief Ends Advance signal

      */
      void endSlaveSignal();

      /**
       * @brief Stop the replica 
       * 
       */
      void stopSlave();

      /**
       * @brief Tell replica to go
       * 
       */
      void goSlave();

      /**
       * @brief stop replica from performing actions 
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

      Motor leftMotor;
      Motor rightMotor;
      PID tapeFollow;
      PID edgeFollow;

      Obstacle rightForwardUltrasonic;
      Obstacle rightMidUltrasonic;
      EdgeBack edgeBack;
      
      BridgeDeploy bridge;

      int countIdolPickUp = 0;

      bool stopped;

      MasterState state;

      Claw leftClaw;
      Claw rightClaw;
      Arm leftArm;
      Arm rightArm;

  };

  class Slave {
    public:
        Slave(): 
        // leftClaw(ClawNS::LEFT_CLAW_SERVO_PIN),
        // rightClaw(ClawNS::RIGHT_CLAW_SERVO_PIN),
        // leftArm(ArmNS::LEFT_ARM_SERVO_PIN, leftClaw, ArmNS::LEFT_HALL_EFFECT_SENSOR_PIN),
        // rightArm(ArmNS::RIGHT_ARM_SERVO_PIN, rightClaw, ArmNS::RIGHT_HALL_EFFECT_SENSOR_PIN),
          //Put Constructors for Claw and zipline 
        state(SlaveState::Inactive) { 
          pinMode(SlaveNS::ADVANCE_MASTER_PIN, OUTPUT);
          pinMode(SlaveNS::STOP_MASTER_PIN, OUTPUT);
          digitalWrite(SlaveNS::ADVANCE_MASTER_PIN, LOW);
          digitalWrite(SlaveNS::STOP_MASTER_PIN,LOW);
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

        // Claw leftClaw;
        // Claw rightClaw;
        // Arm leftArm;
        // Arm rightArm;
        
        /*
        @brief Advances the big bot state

        @returns true if successful, false if unsuccessful (end of list)
        */
        bool advanceState();
    };
} // namespace Robot

#endif
