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

        digitalWrite(SlaveNS::BP_COMM_OUT, LOW);

        break;
      
      case SlaveState::ClawActivateIdolTwo:
        rightArm.placeObjectInContainer();

        rightArm.goThroughArch();
        leftArm.goThroughArch();
        
        advanceState();

        digitalWrite(SlaveNS::BP_COMM_OUT, LOW);

        break;

      // skipping first idol on left (in IR region)

      case SlaveState::ClawActivateIdolFour:
        leftArm.returnToHome();
        delay(500);
        
        rightArm.placeObjectInContainer();
        advanceState();

        digitalWrite(SlaveNS::BP_COMM_OUT, LOW);

        break;

      case SlaveState::BridgeDeploy:
        // need bridge
        bridgeServo.deployBridge();
        advanceState();

        digitalWrite(SlaveNS::BP_COMM_OUT, LOW);

        break;

      case SlaveState::ClawActivateIdolFive:
        leftArm.placeObjectInContainer();
        advanceState();

        digitalWrite(SlaveNS::BP_COMM_OUT, LOW);


      case SlaveState::ClawActivateIdolSix:
        leftArm.placeObjectInContainer();
        advanceState();

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
