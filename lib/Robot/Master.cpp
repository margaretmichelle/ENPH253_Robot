#include <Arduino.h>

#include <Constants.h>
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

           // check if pedastal gets read by sonar (if it does, robot will not tape follow again after picking up idols)
      rightUltrasonic.useObstacle();

      // after picking up second idol (expecting wall to be close (idk if it is within the distance though))
      if (countIdolPickUp == 2 && rightUltrasonic.getDistance() < ObstacleNS::DISTANCE_TO_IDOL) {
        tapeFollow.usePID(o.getTKP(), o.getTKI(), o.getTKD());
        break;
      }

      if (countIdolPickUp == 2 && rightUltrasonic.getDistance() > ObstacleNS::DISTANCE_TO_IDOL) {
        stop(); // robot has passed the archway
        break;
      }

      if (rightUltrasonic.getDistance() > ObstacleNS::DISTANCE_TO_IDOL) {
        tapeFollow.usePID(o.getTKP(), o.getTKI(), o.getTKD());
        break;
      }

      stop();

      if (countIdolPickUp == 0) {
        moveToObjectOnRight();

        digitalWrite(MasterNS::BP_COMM_OUT, HIGH);
        digitalWrite(MasterNS::BP_COMM_OUT, LOW);

        while (slaveBusy) {
          o.displayCustom("Picking up idol:",1);
        }
        countIdolPickUp++;
      } else if (countIdolPickUp == 1) {
        moveToObjectOnRight();

        digitalWrite(MasterNS::BP_COMM_OUT, HIGH);
        digitalWrite(MasterNS::BP_COMM_OUT, LOW);

        while (slaveBusy) {
          o.displayCustom("Picking up idol:",2);
          countIdolPickUp++;
        }
      }

      encoder.pivotAngle(-90);
      encoder.driveDistance(-(rightUltrasonic.getDistance() - 10) * 10);
      while(!tapeFollow.bothOnBlack(TapeFollowerNS::WHITE_THRESHOLD)) {
        moveForCertainTime(80,-80,100); 
      }
      break;

      case MasterState::IRRegion:

        delay(1000);

        encoder.driveStraight(1000,200,o);


        delay(100000000);
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
      break;

    case MasterState::ObstacleFollow:
      //obstacle.useObstacle();

      // o.displayDistance(obstacle.getDistance());
      
      break;

      case MasterState::EdgeFollow:
      
        edgeFollow.usePID(o.getEKP(), o.getEKI(), o.getEKD());

        // o.displayScreen(tapeFollow.getLeftMotorSpeed(), tapeFollow.getRightMotorSpeed(), tapeFollow.getLeftSensorVal(), tapeFollow.getRightSensorVal(), 0, 0, 0, 0, obstacle.getDistance());
        break;

      case MasterState::Done:
        stop();
        break;

    // Testing States

    case MasterState::JustTape:
      tapeFollow.usePID(o.getTKP(), o.getTKI(), o.getTKD());

      o.displayScreen(tapeFollow.getLeftMotorSpeed(), tapeFollow.getRightMotorSpeed(), tapeFollow.getLeftSensorVal(), tapeFollow.getRightSensorVal(), 0,0,0,0);
      break;
    
    case MasterState::TestServos:
      
      delay(500);

      digitalWrite(MasterNS::BP_COMM_OUT, HIGH);
      digitalWrite(MasterNS::BP_COMM_OUT, LOW);

      while (slaveBusy) {
        o.displayCustom("Right: First idol",1);
      }

      delay(800);
      digitalWrite(MasterNS::BP_COMM_OUT, HIGH);
      digitalWrite(MasterNS::BP_COMM_OUT, LOW);

      while (slaveBusy) {
        o.displayCustom("Right: Second idol",2);
      }

      delay(800);
      digitalWrite(MasterNS::BP_COMM_OUT, HIGH);
      digitalWrite(MasterNS::BP_COMM_OUT, LOW);

      while (slaveBusy) {
        o.displayCustom("Left: Third idol",3);
      }

      // delay(800);
      // digitalWrite(MasterNS::BP_COMM_OUT, HIGH);
      // digitalWrite(MasterNS::BP_COMM_OUT, LOW);

      // while (slaveBusy) {
      //   o.displayCustom("Right: Fourth idol",4);
      // }

      // delay(800);
      // digitalWrite(MasterNS::BP_COMM_OUT, HIGH);
      // digitalWrite(MasterNS::BP_COMM_OUT, LOW);

      // while (slaveBusy) {
      //   o.displayCustom("Bridge",0);
      // }

      break;

    case MasterState::PositionandPickUpObject:

      // check sonar distances for 2 seconds
      for (int i = 0; i < 40; i++) {
        leftUltrasonic.useObstacle();
        rightUltrasonic.useObstacle();
        o.displayCustom("Left sonar:", leftUltrasonic.getDistance(), "Right sonar:", rightUltrasonic.getDistance());
        delay(50);
      }

      moveToObjectOnRight();

      digitalWrite(MasterNS::BP_COMM_OUT, HIGH);
      digitalWrite(MasterNS::BP_COMM_OUT, LOW);

      while (slaveBusy) {
        o.displayCustom("Picking up object",0);
      }
      
      break;

    case MasterState::Bridge:
      o.displayCustom("WATCH OUT FOR THE ARMS!",0);

      digitalWrite(MasterNS::BP_COMM_OUT, HIGH);
      digitalWrite(MasterNS::BP_COMM_OUT, LOW);
      while (slaveBusy) {}; // first idol

      digitalWrite(MasterNS::BP_COMM_OUT, HIGH);
      digitalWrite(MasterNS::BP_COMM_OUT, LOW);
      while (slaveBusy) {}; // second idol

      digitalWrite(MasterNS::BP_COMM_OUT, HIGH);
      digitalWrite(MasterNS::BP_COMM_OUT, LOW);
      while (slaveBusy) {}; // third idol

      digitalWrite(MasterNS::BP_COMM_OUT, HIGH);
      digitalWrite(MasterNS::BP_COMM_OUT, LOW);
      while (slaveBusy) {}; // fourth idol

      o.displayCustom("Bridging the gap...",0);
      digitalWrite(MasterNS::BP_COMM_OUT, HIGH);
      digitalWrite(MasterNS::BP_COMM_OUT, LOW);

      while (slaveBusy) {};

      // Find bridge tape?
      encoder.driveDistance(500);

      tapeFollow.usePID(o.getTKP(), o.getTKI(), o.getTKD());
      break;

    case MasterState::JustEdge:
      edgeFollow.usePID(o.getEKP(), o.getEKI(), o.getEKD());

      o.displayScreen(tapeFollow.getLeftMotorSpeed(), tapeFollow.getRightMotorSpeed(), tapeFollow.getLeftSensorVal(), tapeFollow.getRightSensorVal(), edgeBack.getTopLeftSensorVal(), edgeBack.getTopRightSensorVal(), edgeBack.getBottomLeftSensorVal(), edgeBack.getBottomRightSensorVal());
      break;

    case MasterState::UpToArch:
      // check if pedastal gets read by sonar (if it does, robot will not tape follow again after picking up idols)
      rightUltrasonic.useObstacle();

      // after picking up second idol (expecting wall to be close (idk if it is within the distance though))
      if (countIdolPickUp == 2 && rightUltrasonic.getDistance() < ObstacleNS::DISTANCE_TO_IDOL) {
        tapeFollow.usePID(o.getTKP(), o.getTKI(), o.getTKD());
        break;
      }

      if (countIdolPickUp == 2 && rightUltrasonic.getDistance() > ObstacleNS::DISTANCE_TO_IDOL) {
        stop(); // robot has passed the archway
        break;
      }

      if (rightUltrasonic.getDistance() > ObstacleNS::DISTANCE_TO_IDOL) {
        tapeFollow.usePID(o.getTKP(), o.getTKI(), o.getTKD());
        o.displayCustom("Slave state:", slaveBusy);
        break;
      }

      stop();

      delay(100);

      if (countIdolPickUp == 0) {

        o.displayCustom("Slave state:", slaveBusy);

        moveToObjectOnRight();

        digitalWrite(MasterNS::BP_COMM_OUT, HIGH);
        digitalWrite(MasterNS::BP_COMM_OUT, LOW);

        o.displayCustom("Slave state:", slaveBusy);

        while (slaveBusy) {
          o.displayCustom("Picking up idol:",1);
        }
        countIdolPickUp++;
      } else if (countIdolPickUp == 1) {
        moveToObjectOnRight();

        digitalWrite(MasterNS::BP_COMM_OUT, HIGH);
        digitalWrite(MasterNS::BP_COMM_OUT, LOW);

        while (slaveBusy) {
          o.displayCustom("Picking up idol:",2);
          countIdolPickUp++;
        }
      }

      encoder.pivotAngle(-90);
      encoder.driveDistance((rightUltrasonic.getDistance() - 10) * 10);
      while(!tapeFollow.bothOnBlack(TapeFollowerNS::WHITE_THRESHOLD)) {
        moveForCertainTime(80,-80,100); 
      }
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
    if (slaveBusy) slaveBusy = false;
    else slaveBusy = true;
  }

  void Master::shuffleRight() {
    moveForCertainTime(100,0,600);
    moveForCertainTime(0,0,100);
    moveForCertainTime(0,100,600);

    rightUltrasonic.useObstacle();

    moveForCertainTime(0,0,100);

    while (rightUltrasonic.getDistance() > ObstacleNS::DISTANCE_TO_IDOL) {
      moveForCertainTime(-80,-80,100);
      rightUltrasonic.useObstacle();
      moveForCertainTime(0,0,100);
    }

    moveForCertainTime(0,0,100);
  }

  void Master::moveToObjectOnRight() {
    rightUltrasonic.useObstacle();

    encoder.pivotAngle(-90);
    delay(50);
    encoder.driveDistance(-(rightUltrasonic.getDistance() - 15) * 10);
    delay(50);
    encoder.pivotAngle(90);
    delay(50);
  }

  void Master::moveToObjectOnLeft() {
    leftUltrasonic.useObstacle();

    encoder.pivotAngle(90);
    delay(50);
    encoder.driveDistance(-(leftUltrasonic.getDistance() - 15) * 10);
    delay(50);
    encoder.pivotAngle(-90);
    delay(50);
  }

}