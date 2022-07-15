#include <Arduino.h>

#include <Constants.h>
// #include <IR.h>
#include <Motor.h>
#include <PID.h>
#include <Robot.h>
#include <OLED.h>

namespace Robot {
  MasterState Master::poll () {
    // turn off slave signal every loop

    switch(state) {
      case MasterState::Inactive:
        break;

      case MasterState::TapeFollow:

        tapeFollow.usePID(display);

        display.displayScreen();
        break;
  }
    return state;
}  // namespace Robot

}