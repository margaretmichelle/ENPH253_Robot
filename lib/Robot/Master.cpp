#include <Arduino.h>

#include <Constants.h>
// #include <IR.h>
#include <Motor.h>
#include <PID.h>
#include <Robot.h>
#include <OLED.h>

namespace Robot {
  MasterState Master::poll(OLED o, int count)
  {
    // turn off slave signal every loop

    switch (state)
    {
    case MasterState::Inactive:
      break;

    case MasterState::TapeFollow:

      tapeFollow.usePID(o.getKP(), o.getKI(), o.getKD());


      // o.displayScreen();
      // o.displayPID();
      o.displaySpeed(tapeFollow.getLeftMotorSpeed(), tapeFollow.getRightMotorSpeed());
      // o.displayCustom("Left reflectance: ", tapeFollow.getLeftSensorVal(), "Right reflectance: ", tapeFollow.getRightSensorVal());
      // o.displayCustom("Reflectance: ", tapeFollow.getLeftSensorVal(), "Motor speed: ", tapeFollow.getLeftMotorSpeed());

      break;
    }
    return state;
  } // namespace Robot

}