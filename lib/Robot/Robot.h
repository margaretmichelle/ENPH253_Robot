#ifndef Robot_h
#define Robot_h
#include <Arduino.h>
#include <Servo.h>

#include <Constants.h>
#include <Helper.h>
#include <Motor.h>
#include <PID.h>
#include <OLED.h>
#include <Obstacle.h>

namespace Robot {

  /* States */
  enum class MasterState {
    Inactive,
    TapeFollow,
    IRFollow,
    ObstacleFollow, 
    EdgeFollow,
    Done
  };
  enum class SlaveState {
    Inactive,
    ClawOpen,
    Done
  };

  /* Bots */
  class Master {
    public:
      Master():
        leftMotor(MasterNS::LEFT_MOTOR_PIN_1, MasterNS::LEFT_MOTOR_PIN_2),
        rightMotor(MasterNS::RIGHT_MOTOR_PIN_1, MasterNS::RIGHT_MOTOR_PIN_2),
        tapeFollow(PIDType::TapeFollower, leftMotor, rightMotor, 80),
        edgeFollow(PIDType::EdgeFollower, leftMotor, rightMotor, 80),
        obstacle(),
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
      MasterState poll(OLED o, int count);

      /**
       * @brief Set the state of slave. ONLY FOR DEBUGGING. Do not use on competition day
       */
      void setState(MasterState state) { this->state = state; }

    private:
      /*
      @brief Increase the master state

      @returns true if successful, false if unsuccessful (out of states)
      */
      bool incrementState();

      /*
      @brief Advances the slave state

      */
      void signalReplicaAdvance();

      /*
      @brief Ends Advance signal

      */
      void endReplicaSignal();

      void stopReplica();

      void goReplica();

      void stop();

      Motor leftMotor;
      Motor rightMotor;
      PID tapeFollow;
      PID edgeFollow;

      Obstacle obstacle;

      bool stopped;

      MasterState state;

  };

  class Slave {
    public:
        Slave(): 
          //Put Constructors for Claw and zipline 
        state(SlaveState::Inactive) {

        }


        /*
        @brief Returns current state of robot and performs action for one loop.
        */
        SlaveState poll();
        /**
         * @brief Set the state of master. ONLY FOR DEBUGGING. Do not use on competition day
         */
        void setState(SlaveState state) { this->state = state; }

        /**
         * @brief move slave for given time
         */
        void moveForTime(int leftMotorSpeed, int rightMotorSpeed, int moveTime);

    private:
        SlaveState state;
        bool stopped;
        void stop();
        
        /*
        @brief Advances the big bot state

        @returns true if successful, false if unsuccessful (end of list)
        */
        bool advanceState();
    };
} // namespace Robot

#endif
