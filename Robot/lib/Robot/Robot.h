#ifndef Robot_h
#define Robot_h
#include <Arduino.h>
#include <Servo.h>

#include <Constants.h>
#include <Helper.h>
#include <Motor.h>
#include <PID.h>

namespace Robot {

  /* States */
  enum class MasterState {
    Inactive,
    TapeFollow,
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
        tapeFollow(PIDType::TapeFollower, leftMotor, rightMotor, 100),
        state(MasterState::Inactive) {
            //Set-up Communication Pins
        }

      /*
      @brief Returns current state of robot and performs action for one loop.
      */
      MasterState poll();

      /**
       * @brief Set the state of slave. ONLY FOR DEBUGGING. Do not use on competition day
       */
      void setState(MasterState state) { this->state = state; }

    private:
      /*
      @brief Advances the master state

      @returns true if successful, false if unsuccessful (out of states)
      */
      bool advanceState();

      /*
      @brief Advances the slave state

      */
      void signalSlaveAdvance();

      /*
      @brief Ends Advance signal

      */
      void endSlaveSignal();

      void stopSlave();

      void goSlave();

      Motor leftMotor;
      Motor rightMotor;
      PID tapeFollow;

      MasterState state;

  };
} // namespace Robot

#endif
