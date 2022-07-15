#include <Arduino.h>

#include <Constants.h>
#include <IR.h>
#include <Motor.h>
#include <PID.h>

#include <Robot.h>

namespace Robot {
  MasterState Master::poll () {
    // turn off slave signal every loop

    switch(state) {
      case MasterState::Inactive:
        break;

      case MasterState::TapeFollow:
        //flat ground
        tapeFollow.setKP(5);
        tapeFollow.setKD(1);
        tapeFollow.setKI(0);

        tapeFollow.usePID();
        break;
  }
    return state;
}  // namespace Robot

}