#include <Arduino.h>
#include <Constants.h>
#include <Encoder.h>
#include <Motor.h>
#include <PID.h>
#include <OLED.h>


Motor leftMotor(MasterNS::LEFT_MOTOR_PIN_1, MasterNS::LEFT_MOTOR_PIN_2);
Motor rightMotor(MasterNS::RIGHT_MOTOR_PIN_1, MasterNS::RIGHT_MOTOR_PIN_2);

Encoder::Encoder(){
    pinMode(EncoderNS::LEFT_ENCODER_CLK_PIN, INPUT);
    pinMode(EncoderNS::RIGHT_ENCODER_CLK_PIN, INPUT);
    pinMode(EncoderNS::LEFT_ENCODER_DT_PIN, INPUT);
    pinMode(EncoderNS::RIGHT_ENCODER_DT_PIN, INPUT);

    attachInterrupt(digitalPinToInterrupt(EncoderNS::LEFT_ENCODER_CLK_PIN), std::bind(&Encoder::leftEncoderPulse, this), RISING);
    attachInterrupt(digitalPinToInterrupt(EncoderNS::RIGHT_ENCODER_CLK_PIN), std::bind(&Encoder::rightEncoderPulse, this), RISING);

    leftEncoderPulses = 0;
    rightEncoderPulses = 0;
}

void Encoder::driveStraight(int distanceMm, int motorSpeed, OLED o){
    int adjustmentFactor = 1;

    // Sets target number of counts for the encoder
    float numOfRevs = distanceMm / EncoderNS::ROTATION_DISTANCE_MM;
    int targetRadians = numOfRevs * 2 * PI;

    if (distanceMm < 0 ){
        adjustmentFactor = -1;
    }

    // Sets inital encoder counts to keep track of new changes to encoder counts
    int initalLeftCount = leftEncoderPulses;
    int initalRightCount = rightEncoderPulses;

    int lastRotError = 0;
    int lastRadiansError = 0;
    int startingTime = millis();
    int lastTime = startingTime;

    //travels until one wheel reaches the end
    while ( (leftEncoderPulses - initalLeftCount) /* EncoderNS::PULSES_PER_RAD != targetRadians || EncoderNS::PULSES_PER_RAD != targetCount */ ){
        //Set sample pulse count
        int currentLeftCount = leftEncoderPulses;
        int currentRightCount = rightEncoderPulses;

        //Find net change in pulse counts from beggining
        int diffLeft = currentLeftCount - initalLeftCount;
        int diffRight = currentRightCount - initalRightCount;

        int currentTime = millis();

        //Find rotational velocities relative to start
        int leftRotVelocity = diffLeft / (currentTime - startingTime) / EncoderNS::PULSES_PER_RAD * 1000;
        int rightRotVelocity = diffLeft / (currentTime - startingTime) / EncoderNS::PULSES_PER_RAD * 1000; 

        //Find rotational and derivative rotational errors
        int rotError = leftRotVelocity - rightRotVelocity;
        int derivativeRotError = (rotError - lastRotError)/(currentTime - lastTime);

        lastRotError = rotError;

        //Find the rotational adjustment
        int rotAdjustment = (EncoderNS::ROT_KP * rotError) + (EncoderNS::ROT_KD * derivativeRotError);

        //Find the average radians distance travelled and error and derivative error
        int avgRadians = (diffLeft+diffRight)/2*EncoderNS::PULSES_PER_RAD;
        int radiansError = targetRadians - avgRadians;
        int derivativeRadiansError = (radiansError - lastRadiansError)/(currentTime - lastTime);

        lastRadiansError = radiansError;
        lastTime = currentTime;

        // //Make adjustment for radians distance
        // int radiansAdjustment = int ((EncoderNS::DIST_KP*distanceError) + (EncoderNS::DIST_KD * derivativeDistanceError));

        //Update motor speeds
        // int leftMotorSpeed = (motorSpeed - rotAdjustment + radiansAdjustment) * adjustmentFactor;
        // int rightMotorSpeed = (motorSpeed + rotAdjustment + radiansAdjustment) * adjustmentFactor;
        // leftMotor.speed(leftMotorSpeed);
        // rightMotor.speed(rightMotorSpeed);

        //Delay to give motors time to adjust velocities
        delay(10);
    }

    //stop moving motors
    leftMotor.stop();
    rightMotor.stop();
    delay(500);
}

void Encoder::driveDistance(int distance, int motorSpeed) {

    // use wheel encoders to drive straight for specified distance at specified power

    // set initial power for left and right motors
    int leftSpeed = motorSpeed;
    int rightSpeed = motorSpeed;

    // amount to offset motor powers to drive straight
    int offset = 5;

    // if negative distance, make motor powers & offset also negative
    if (distance < 0) {
        leftSpeed *= -1;
        rightSpeed *= -1;
        offset *= -1;
    }

    // use correction to improve distance accuracy
    // adjust correction value based on test results
    float correction = -1.0; // need decimal point for float value
    if (distance > 0) distance += correction;
    else if (distance < 0) distance -= correction;

    // variables for tracking wheel encoder counts
    long leftCount = 0;
    long rightCount = 0;
    long prevLeftCount = 0;
    long prevRightCount = 0;
    long leftDiff, rightDiff;

    // based on distance, calculate number of wheel revolutions
    float numRev = distance / EncoderNS::ROTATION_DISTANCE_MM;

    // calculate target encoder count
    float targetCount = numRev * EncoderNS::PULSES_PER_ROTATION;

    // reset encoder counters and start driving
    leftEncoderPulses = 0;
    rightEncoderPulses = 0;
    delay(100);
    leftMotor.speed(leftSpeed);
    rightMotor.speed(rightSpeed);

    // keeps looping while right encoder count less than target count
    while (abs(rightCount) < abs(targetCount)) {

        // get current wheel encoder counts
        leftCount = leftEncoderPulses;
        rightCount = rightEncoderPulses;

        // calculate increase in count from previous reading
        leftDiff = abs(leftCount - prevLeftCount);
        rightDiff = abs(rightCount - prevRightCount);

        // store current counts as "previous" counts for next reading
        prevLeftCount = leftCount;
        prevRightCount = rightCount;

        // adjust left & right motor powers to keep counts similar (drive straight)

        // if left rotated more than right, slow down left & speed up right
        if (leftDiff > rightDiff) {
            leftSpeed = leftSpeed - offset;
            rightSpeed = rightSpeed + offset;
        }
        // else if right rotated more than left, speed up left & slow down right
        else if (leftDiff < rightDiff) {
            leftSpeed = leftSpeed + offset;
            rightSpeed = rightSpeed - offset;
        }

        // apply adjusted motor powers
        leftMotor.speed(leftSpeed);
        rightMotor.speed(rightSpeed);
        delay(10);  // short delay before next reading
    }

    // target count reached
    leftMotor.stop();
    rightMotor.stop();
    delay(1000); // brief delay to wait for complete stop
}


void Encoder::pivotAngle(float angleDegrees) {
// use wheel encoders to pivot (turn) by specified angle

    // set motor speed for pivoting
    int speed = EncoderNS::PIVOT_WHEEL_SPEED; // clockwise
    int angle = angleDegrees;

    if (angleDegrees < 0) {
        speed *= -1; 
    }

    // use correction to improve angle accuracy
    // adjust correction value based on test results
    float correction = -10.0; // need decimal point for float value
    if (angle > 0) {
        angle += correction; 
    }
    else if (angle < 0) {
        angle -= correction;
    }

    // variable for tracking wheel encoder counts
    long rightCount = 0;

    // based on angle, calculate distance (arc length) for pivot
    float distance = abs(angle) / 360.0 * EncoderNS::PIVOT_CIRCUMFERENCE;

    // based on distance, calculate number of wheel revolutions
    float numRev = distance / EncoderNS::ROTATION_DISTANCE_MM;

    // based on number of revolutions, calculate target encoder count
    float targetCount = numRev * EncoderNS::PULSES_PER_ROTATION;

    // reset encoder counters and start pivoting
    leftEncoderPulses = 0;
    rightEncoderPulses = 0;
    delay(100);
    leftMotor.speed(speed);
    rightMotor.speed(-speed); //will go counterclockwise if angle is - therefore speeds will be negative 

    // keeps looping while right encoder count less than target count
    while (abs(rightCount) < abs(targetCount)) {
        // get current wheel encoder count
        rightCount = rightEncoderPulses;
        delay(10);  // short delay before next reading
    }

    // target count reached
    leftMotor.stop();
    rightMotor.stop();
    delay(800);
}

void Encoder::leftEncoderPulse(){
    // if (digitalRead(EncoderNS::LEFT_ENCODER_DT_PIN) == LOW){
        leftEncoderPulses++;
    // }
    // else {
    //     leftEncoderPulses--;
    // }
}

void Encoder::rightEncoderPulse(){
    // if (digitalRead(EncoderNS::RIGHT_ENCODER_DT_PIN)== HIGH){
        rightEncoderPulses++;
    // }
    // else{
    //     rightEncoderPulses--;
    // }
}

void Encoder::resetPulses(){
    leftEncoderPulses = 0;
    rightEncoderPulses = 0;
}

