#include <Arduino.h>

#include <Constants.h>
// #include <IR.h>
#include <Motor.h>
#include <PID.h>
#include <Robot.h>
#include <OLED.h>

namespace Robot {
  MasterState Master::poll(OLED o) {
    // turn off slave signal every loop
    endSlaveSignal();

    switch (state) {
      case MasterState::Inactive:
        //We will probably not have an inactive masterState
        incrementState();
        break;

      case MasterState::TapeFollow:

        // tapeFollow.usePID(o.getTKP(), o.getTKI(), o.getTKD());
        
        moveForCertainTime(200,200,500);
        delay(1000);
        moveForCertainTime(-200,-200,500);
        delay(500);
        moveForCertainTime(150,100,500);
        delay(500);
        moveForCertainTime(100,150,500);

      // o.displayScreen(tapeFollow.getLeftMotorSpeed(), tapeFollow.getRightMotorSpeed(), tapeFollow.getLeftSensorVal(), tapeFollow.getRightSensorVal(), 0, 0, 0, 0, obstacle.getDistance());

      // obstacle.useObstacle();

      // if(obstacle.getDistance() < ObstacleNS::DISTANCE_TO_IDOL && countIdolPickUp == 0) {
      //   moveForCertainTime(0,0,300); //stop for 300 ms 

      //   //Hardcode the first turn using moveForCertainTime()

      //   moveForCertainTime(90,80,800);
      //   moveForCertainTime(-80,-120,800); //these are just placeholders for the specific turns
      //   moveForCertainTime(0,0,100); //stop to prepare claw 

      //   //Add claw code 
      //   rightArm.placeObjectInContainer();

      //   countIdolPickUp++;

        
      //   //Refind Tape and hardcode some good angle to continually move at 
      //   while(!tapeFollow.bothOnBlack(TapeFollowerNS::WHITE_THRESHOLD)) {
      //       moveForCertainTime(80,120,100);
      //   }
      // }
      // else if(obstacle.getDistance() < ObstacleNS::DISTANCE_TO_IDOL && countIdolPickUp == 1) {
      //   moveForCertainTime(0,0,300); //stop for 300 ms

      //   //Hardcode the second turn using moveForCertainTime()
      //   moveForCertainTime(90,80,800);
      //   moveForCertainTime(-80,-120,800); //these are just placeholders for the specific turns
      //   moveForCertainTime(0,0,100); //stop to prepare claw 

      //   //Add claw code
      //   rightArm.placeObjectInContainer();

      //   countIdolPickUp++;

        
      //   //Refind Tape and hardcode some good angle to continually move at probably will want to have a sharper turn for this one 
      //   while(!tapeFollow.bothOnBlack(TapeFollowerNS::WHITE_THRESHOLD)) {
      //       moveForCertainTime(80,120,100);
      //   }
      // }
      
      break;

      case MasterState::IRFollow:

        encoder.pivotAngle(45.0);
        encoder.driveStraight(1000,200);
        // obstacle.useObstacle();

        // tapeFollow.usePID(o.getTKP(), o.getTKI(), o.getTKD());

        // if(obstacle.getDistance() < ObstacleNS::DISTANCE_TO_IDOL && countIdolPickUp == 0) {
        //   moveForCertainTime(0,0,2000);

        //   //Hardcode the first turn using moveForCertainTime()

        //   moveForCertainTime(-110,-60,800);
        //   moveForCertainTime(80,80,420); //these are just placeholders for the specific turns
        //   moveForCertainTime(110,60,500);
        //   obstacle.useObstacle();
        //   while (obstacle.getDistance() > 15) {
        //     moveForCertainTime(-80,-80,100);
        //     obstacle.useObstacle();
        //   }
        //   moveForCertainTime(0,0,2000); //stop to prepare claw 
        //   rightArm.goDown();
        //   rightArm.returnToHome();
          
        //   while(!tapeFollow.bothOnBlack(TapeFollowerNS::BLACK_THRESHOLD)) {
        //       moveForCertainTime(150,70,100);
        //   }

    case MasterState::ObstacleFollow:
      // obstacle.useObstacle();

      // o.displayDistance(obstacle.getDistance());
      
      break;

      case MasterState::EdgeFollow:
      
        edgeFollow.usePID(o.getEKP(), o.getEKI(), o.getEKD());

        // o.displayScreen(tapeFollow.getLeftMotorSpeed(), tapeFollow.getRightMotorSpeed(), tapeFollow.getLeftSensorVal(), tapeFollow.getRightSensorVal(), 0, 0, 0, 0, obstacle.getDistance());
        break;

      case MasterState::Done:
        stop();
        break;

    // Testing and Time Trials States

    case MasterState::JustTape:
      tapeFollow.usePID(o.getTKP(), o.getTKI(), o.getTKD());

      o.displayScreen(tapeFollow.getLeftMotorSpeed(), tapeFollow.getRightMotorSpeed(), tapeFollow.getLeftSensorVal(), tapeFollow.getRightSensorVal(), 0,0,0,0);
      break;
    
    case MasterState::PickUpObject:
    // o.displayScreen(tapeFollow.getLeftMotorSpeed(), tapeFollow.getRightMotorSpeed(), tapeFollow.getLeftSensorVal(), tapeFollow.getRightSensorVal(), 0, 0, 0, 0);

      delay (1000);

      //rightArm.placeObjectInContainer();

      break;

    case MasterState::PositionObject:
      rightForwardUltrasonic.useObstacle();

      o.displayCustom("Front sonar: ", rightForwardUltrasonic.getDistance());
      
      while (rightForwardUltrasonic.getDistance() <= ObstacleNS::DISTANCE_TO_IDOL && rightForwardUltrasonic.getDistance() > 15) {
        shuffleRight();
      }
      
      break;

    case MasterState::Bridge:
      bridge.deployBridge();
      tapeFollow.usePID(o.getTKP(), o.getTKI(), o.getTKD());
      break;

    case MasterState::JustEdge:
      edgeFollow.usePID(o.getEKP(), o.getEKI(), o.getEKD());

      o.displayScreen(tapeFollow.getLeftMotorSpeed(), tapeFollow.getRightMotorSpeed(), tapeFollow.getLeftSensorVal(), tapeFollow.getRightSensorVal(), edgeBack.getTopLeftSensorVal(), edgeBack.getTopRightSensorVal(), edgeBack.getBottomLeftSensorVal(), edgeBack.getBottomRightSensorVal());
      break;

    case MasterState::UpToArch:
      tapeFollow.usePID(o.getTKP(), o.getTKI(), o.getTKD());

      rightForwardUltrasonic.useObstacle();

      while (rightForwardUltrasonic.getDistance() <= ObstacleNS::DISTANCE_TO_IDOL && rightForwardUltrasonic.getDistance() > 15) {
        shuffleRight();
      }

      //rightArm.placeObjectInContainer();

      break;

    default:
      break;
    }
  
    return state;
  } // namespace Robot

  void Master::useEdgeDetection() {
    edgeBack.useEdge();
  }



  void Master::stop() {
    // if(stopped) { return; }
    // stopped = true;
    leftMotor.stop();
    rightMotor.stop();
  }

  void Master::moveForCertainTime(int leftMotorSpeed,int rightMotorSpeed, int moveForTime) {
     leftMotor.speed(leftMotorSpeed);
     rightMotor.speed(rightMotorSpeed);
     delay(moveForTime);

     leftMotor.stop();
     rightMotor.stop();
  }

  bool Master:: incrementState() {
    if (state == MasterState::Done) {
      return false;
    } else {
      state = static_cast<MasterState>(static_cast<int>(state) + 1);
      return true;
    }
  }

  void Master::endSlaveSignal() {
    digitalWrite(MasterNS::BP_COMM_OUT, LOW);
  }

  void Master::stopSlave() {
    digitalWrite(MasterNS::BP_COMM_OUT, HIGH);
    //Ensure slave has stopped before doing other things 
    delay(500);
  }

  void Master::goSlave() {
    digitalWrite(MasterNS::BP_COMM_OUT, LOW);
  }

  void Master::changeSlaveState() {
    slaveBusy = false;
  }

  void Master::shuffleRight() {
    moveForCertainTime(100,0,600);
    moveForCertainTime(0,0,100);
    moveForCertainTime(0,100,600);

    rightForwardUltrasonic.useObstacle();

    moveForCertainTime(0,0,100);

    while (rightForwardUltrasonic.getDistance() > ObstacleNS::DISTANCE_TO_IDOL) {
      moveForCertainTime(-80,-80,100);
      rightForwardUltrasonic.useObstacle();
      moveForCertainTime(0,0,100);
    }

    moveForCertainTime(0,0,100);
  }

}