#include <Arduino.h>
#include <Servo.h>

#include <Constants.h>
#include <Motor.h>

#include <Robot.h>

namespace Robot {
  SlaveState Slave::poll () {

    switch(state) {
      case SlaveState::Inactive:
        // keep track of start time
        stop();
        break;

      case SlaveState::Done:
        // complete, so do nothing
        stop();
        break;
    }
    return state;
  }

  bool Slave::advanceState() {
    if (state == SlaveState::Done) { return false; }
    state = static_cast<SlaveState>(static_cast<int>(state) + 1);
    return true;
  }

  void Slave::stop() {
    if(stopped) { return; }
    stopped = true;
  }
}  // namespace Order66
