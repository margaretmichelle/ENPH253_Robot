#include <Arduino.h>

#include <Constants.h>
#include <Motor.h>
#include <PID.h>
#include <Robot.h>
#include <OLED.h>

namespace Robot {
  MasterState Master::poll(OLED o) {

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
        // moveToObjectOnRight();

        digitalWrite(MasterNS::BP_COMM_OUT, HIGH);
        digitalWrite(MasterNS::BP_COMM_OUT, LOW);

        while (slaveBusy) {
          o.displayCustom("Picking up idol:",1);
        }
        countIdolPickUp++;
      } else if (countIdolPickUp == 1) {
        // moveToObjectOnRight();

        digitalWrite(MasterNS::BP_COMM_OUT, HIGH);
        digitalWrite(MasterNS::BP_COMM_OUT, LOW);

        while (slaveBusy) {
          o.displayCustom("Picking up idol:",2);
          countIdolPickUp++;
        }
      }

      // encoder.pivotAngle(-90);
      // encoder.driveDistance(-(rightUltrasonic.getDistance() - 10) * 10);
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

      o.displayCustom("Right: First idol",1);
      sendSlaveSignalandWait();

      delay(800);
      
      o.displayCustom("Right: Second idol",2);
      sendSlaveSignalandWait();

      delay(800);

      o.displayCustom("Left: Third idol",3);
      sendSlaveSignalandWait();

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

      // // check sonar distances for 2 seconds
      // for (int i = 0; i < 40; i++) {
      //   leftUltrasonic.useObstacle();
      //   rightUltrasonic.useObstacle();
      //   o.displayCustom("Left sonar:", leftUltrasonic.getDistance(), "Right sonar:", rightUltrasonic.getDistance());
      //   delay(50);
      // }

      // moveToObjectOnRight(rightUltrasonic.getDistance());

      // o.displayCustom("Picking up object",0);
      // sendSlaveSignalandWait();

        encoder.driveDistance(1200,200);

        do {
          rightUltrasonic.useObstacle();
          encoder.driveDistance(-25,100);
        } while(rightUltrasonic.getDistance() > ObstacleNS::DISTANCE_TO_IDOL);

        countIdolPickUp =+ 2;
        
        moveToObjectOnRight(rightUltrasonic.getDistance());
        sendSlaveSignalandWait();
        countIdolPickUp++;

        encoder.driveDistance(-100,150);

        encoder.pivotAngle(90);

        bridge.edgeAlign();

        delay(2000);
      
      break;

    case MasterState::Bridge:
      o.displayCustom("WATCH OUT FOR THE ARMS!",0);

      sendSlaveSignalandWait(); // first idol

      sendSlaveSignalandWait(); // second idol

      sendSlaveSignalandWait(); // fourth idol

      encoder.driveDistance(-50,100);

      o.displayCustom("Bridging the gap...",0);
      sendSlaveSignalandWait();
      
      edgeFollow.usePID(o.getEKP(), o.getEKI(), o.getEKD());

      delay(1200);

      do {
          rightUltrasonic.useObstacle();
          encoder.driveDistance(30,100);
        } while(rightUltrasonic.getDistance() > ObstacleNS::DISTANCE_TO_IDOL);

      moveToObjectOnLeft(leftUltrasonic.getDistance());
      sendSlaveSignalandWait();
      countIdolPickUp++;

      encoder.pivotAngle(90);

      do {
        rightUltrasonic.useObstacle();
        edgeFollow.usePID(o.getEKP(), o.getEKI(), o.getEKD());
      } while (rightUltrasonic.getDistance() > 45);

      encoder.pivotAngle(45);

      do {
        leftUltrasonic.useObstacle();
        encoder.driveDistance(50,120);
      } while (leftUltrasonic.getDistance() > ObstacleNS::DISTANCE_TO_IDOL);

      moveToObjectOnLeft(leftUltrasonic.getDistance());
      sendSlaveSignalandWait();
      countIdolPickUp++;

      stop();
      delay(10000);

      break;

    case MasterState::JustEdge:
      edgeFollow.usePID(o.getEKP(), o.getEKI(), o.getEKD());

      o.displayScreen(tapeFollow.getLeftMotorSpeed(), tapeFollow.getRightMotorSpeed(), tapeFollow.getLeftSensorVal(), tapeFollow.getRightSensorVal(), edgeBack.getTopLeftSensorVal(), edgeBack.getTopRightSensorVal(), edgeBack.getBottomLeftSensorVal(), edgeBack.getBottomRightSensorVal());
      break;

    case MasterState::UpToArch:
      timeOnCourse = millis() / 1000;

      // turn off sonar when not needed, only tape follow
      if (timeOnCourse <= 8 || (countIdolPickUp == 1 && (timeOnCourse - timeOfIdolPickup) <= 7)) {
        tapeFollow.usePID(o.getTKP(), o.getTKI(), o.getTKD());
        break;
      }

      rightUltrasonic.useObstacle();

      // after picking up second idol (expecting wall to be close (idk if it is within the distance though))
      if (countIdolPickUp == 2 && rightUltrasonic.getDistance() < ObstacleNS::DISTANCE_TO_IDOL) {
        tapeFollow.usePID(o.getTKP(), o.getTKI(), o.getTKD());
        rightUltrasonic.useObstacle();

        if (rightUltrasonic.getDistance() > ObstacleNS::DISTANCE_TO_IDOL) {
          stop(); // robot has passed the archway

          delay(1000);

          // encoder.pivotAngle(15);

          encoder.driveDistance(1200,200);

          do {
            rightUltrasonic.useObstacle();
            encoder.driveDistance(-50,120);
          } while(rightUltrasonic.getDistance() > ObstacleNS::DISTANCE_TO_IDOL);
          
          moveToObjectOnRight(rightUltrasonic.getDistance());
          sendSlaveSignalandWait();
          countIdolPickUp++;

          encoder.driveDistance(180,150);

          encoder.pivotAngle(90);

          bridge.edgeAlign();

          delay(2000);
        }

        break;
      }


      if (rightUltrasonic.getDistance() > ObstacleNS::DISTANCE_TO_IDOL) {
        tapeFollow.usePID(o.getTKP(), o.getTKI(), o.getTKD());
        break;
      }

      stop();

      delay(500);

      moveToObjectOnRight(rightUltrasonic.getDistance());
      sendSlaveSignalandWait();
      delay(500);
      countIdolPickUp++;

      timeOfIdolPickup = millis() / 1000;

      delay(200);

      if (countIdolPickUp == 1) {
       encoder.pivotAngle(-75); 
      } else {
        encoder.pivotAngle(-55);
        encoder.driveDistance(-75, 100);
      }
      while(!tapeFollow.bothOnBlack(TapeFollowerNS::WHITE_THRESHOLD)) {
        moveForCertainTime(75,-75,90); 
      }

      delay(300);

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

  void Master::sendSlaveSignalandWait() {
    digitalWrite(MasterNS::BP_COMM_OUT, HIGH);
    digitalWrite(MasterNS::BP_COMM_OUT, LOW);
    delay(500);

    while (slaveBusy) {}
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

  void Master::moveToObjectOnRight(long initalDistance) {
    do {
      encoder.driveDistance(-15, 80); // counteract drift
      rightUltrasonic.useObstacle();
    } while (rightUltrasonic.getDistance() >= initalDistance + 1);

    encoder.driveDistance(-18, 90);

    // if (initalDistance >= 13 && initalDistance <= 14) {
    //   return;
    // }

    switch (countIdolPickUp) {
      case 0:
        encoder.driveDistance(-20, 90);
        break;
      case 1:
        encoder.driveDistance(-13, 90);
        break;
      default:
        encoder.pivotAngle(-90);
        encoder.driveDistance(-(initalDistance - 15) * 10, 80);
        encoder.pivotAngle(90);
        break;
    }
  }

  void Master::moveToObjectOnLeft(long initalDistance) {
    do {
      encoder.driveDistance(-15, 80); // counteract drift
      leftUltrasonic.useObstacle();
    } while (leftUltrasonic.getDistance() >= initalDistance + 1);

    encoder.driveDistance(-25, 100);

    if (initalDistance >= 13 && initalDistance <= 15) {
      return;
    }

    encoder.pivotAngle(90);
    encoder.driveDistance(-(initalDistance - 15) * 10, 80);
    encoder.pivotAngle(-90);
  }

}