#include <Constants.h>
#include <Helper.h>

#include <BridgeServo.h>
#include <ServoMotor.h>

BridgeServos::BridgeServos() : 
    unHookServo(BridgeDeployNS::UnHookBridge::UNHOOK_BRIDGE_SERVO_PIN)
  {
    unHookServo.setupServo(BridgeDeployNS::SERVO_REST_ANGLE);
  }
  
void BridgeServos::deployBridge() {
    //wait a second for robot to fully stop
    delay(1000);
    //deploy bridge
    unHookServo.write(BridgeDeployNS::UNHOOK_SERVO_FINAL_ANGLE);
    delay(2000); //wait a bit to make sure unhooked 
}