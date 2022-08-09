#include <Arduino.h>

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

      case SlaveState::ClawActivateIdolOne:
        rightArm.placeObjectInContainer();
        advanceState();
        delay(100);
        digitalWrite(SlaveNS::BP_COMM_OUT, LOW);

        break;
      
      case SlaveState::ClawActivateIdolTwo:
        rightArm.placeObjectInContainer();
        advanceState();
        delay(100);
        digitalWrite(SlaveNS::BP_COMM_OUT, LOW);

        break;

      case SlaveState::ClawActivateIdolThree:
        leftArm.placeObjectInContainer();
        advanceState();
        delay(100);
        digitalWrite(SlaveNS::BP_COMM_OUT, LOW);

        break;

      case SlaveState::ClawActivateIdolFour:
        rightArm.placeObjectInContainer();
        advanceState();
        delay(100);
        digitalWrite(SlaveNS::BP_COMM_OUT, LOW);

        break;

      case SlaveState::BridgeDeploy:
        // need bridge
        advanceState();
        delay(100);
        digitalWrite(SlaveNS::BP_COMM_OUT, LOW);

        break;

      case SlaveState::ClawActivateIdolFive:
        // leftArm.placeObjectInContainer();
        advanceState();
        delay(100);
        digitalWrite(SlaveNS::BP_COMM_OUT, LOW);


      case SlaveState::ClawActivateIdolSix:
        // rightArm.placeObjectInContainer(); //Don;t know which one 
        advanceState();
        delay(100);
        digitalWrite(SlaveNS::BP_COMM_OUT, LOW);
        break;

      case SlaveState::Done:
        // complete, so do nothing and stop the replica/slave 
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
