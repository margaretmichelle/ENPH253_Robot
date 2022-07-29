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
        //send signal for master to GOOOO
        break;
      
      case SlaveState::ClawActivateIdolTwo:
        rightArm.placeObjectInContainer();
        advanceState();
                //send signal for master to GOOOO

        break;

      case SlaveState::ClawActivateIdolThree:
        leftArm.placeObjectInContainer(); //probably left arm 
        advanceState();
                //send signal for master to GOOOO

        break;

      case SlaveState::ClawActivateIdolFour:
        rightArm.placeObjectInContainer();
        advanceState();
                //send signal for master to GOOOO

        break;

      case SlaveState::BridgeDeploy:
        advanceState();
              //send signal for master to GOOOO
        break;

      case SlaveState::ClawActivateIdolFive:
        leftArm.placeObjectInContainer();
        advanceState();
                //send signal for master to GOOOO


      case SlaveState::ClawActivateIdolSix:
        rightArm.placeObjectInContainer(); //Don;t know which one 
        advanceState();
                //send signal for master to GOOOO





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
