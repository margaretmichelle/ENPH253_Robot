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
      //
      incrementState();
      break;

    case MasterState::TapeFollow:

      tapeFollow.usePID(o.getKP(), o.getKI(), o.getKD());


      // o.displayScreen();
      // o.displayPID();
      o.displaySpeed(tapeFollow.getLeftMotorSpeed(), tapeFollow.getRightMotorSpeed());
      // o.displayCustom("Left reflectance: ", tapeFollow.getLeftSensorVal(), "Right reflectance: ", tapeFollow.getRightSensorVal());
      // o.displayCustom("Reflectance: ", tapeFollow.getLeftSensorVal(), "Motor speed: ", tapeFollow.getLeftMotorSpeed());

      break;

    case MasterState::IRFollow:

      break;

    case MasterState::ObstacleFollow:
      obstacle.useObstacle();

      o.displayDistance(obstacle.getDistance());
      
      break;

    case MasterState::EdgeFollow:
    
      edgeFollow.usePID(o.getKP(), o.getKI(), o.getKD());
      break;

    case MasterState::Done:
      stop();
      break;

    default:
      break;
    }
  
    return state;
  } // namespace Robot

  void Master::stop() {
    if(stopped) { return; }
    stopped = true;
    leftMotor.stop();
    rightMotor.stop();
  }

  bool Master:: incrementState() {
    if (state == MasterState::Done) {
      return false;
    }
    else {
      state = static_cast<MasterState>(static_cast<int>(state) + 1);
      return true;
    }
  }

  void Master::endReplicaSignal() {
    digitalWrite(MasterNS::ADVANCE_SLAVE_PIN, LOW);
  }

  void Master::stopReplica() {
    digitalWrite(MasterNS::STOP_SLAVE_PIN, HIGH);
    //Ensure slave has stopped before doing other things 
    delay(500);
  }

  void Master::goReplica() {
    digitalWrite(MasterNS::STOP_SLAVE_PIN, LOW);
  }

  

}