#ifndef BridgeServos_h
#define BridgeServos_h

#include <Constants.h>
#include <Helper.h>
#include <ServoMotor.h>

class BridgeServos {
    public:

    BridgeServos();

    /**
   * @brief deploy bridge. Puts servo in bridge release angle, then put it back
   */
    void deployBridge();


    private:
    
    ServoMotor unHookServo;


};

#endif