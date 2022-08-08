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

    attachInterrupt(digitalPinToInterrupt(EncoderNS::LEFT_ENCODER_CLK_PIN), std::bind(&Encoder::leftEncoderPulse, this), RISING);
    attachInterrupt(digitalPinToInterrupt(EncoderNS::RIGHT_ENCODER_CLK_PIN), std::bind(&Encoder::rightEncoderPulse, this), RISING);

    leftEncoderPulses = 0;
    rightEncoderPulses = 0;
}

void Encoder::driveStraight(float distance, int motorSpeed, OLED o){

    float correction = -200.0;

    // Sets target number of counts for the encoder
    float numOfRevs = abs(distance + correction) / EncoderNS::ROTATION_DISTANCE_MM;
    unsigned long targetCount = numOfRevs * EncoderNS::PULSES_PER_ROTATION;

    // Sets inital encoder counts to keep track of new changes to encoder counts
    unsigned long initalLeftCount = leftEncoderPulses;
    unsigned long initalRightCount = rightEncoderPulses;

    unsigned long lastRotError = 0;
    unsigned long lastDistanceError = 0;

    //travels until one wheel reaches the end
    while ( (leftEncoderPulses - initalLeftCount) < targetCount && rightEncoderPulses - initalRightCount < targetCount ){
        // Chooses a sample count, have to do it this way since the interupted value will constantly change
        unsigned long currentLeftCount = leftEncoderPulses;
        unsigned long currentRightCount = rightEncoderPulses;


        //Looks at the change in encoder pulses from the initial code to see what motor needs to travel more
        unsigned long diffLeft = currentLeftCount - initalLeftCount;
        unsigned long diffRight = currentRightCount - initalRightCount;

        unsigned long rotError = diffLeft - diffRight;
        unsigned long derivativeRotError = rotError - lastRotError;
        lastRotError = rotError;

        int rotAdjustment = int ((EncoderNS::ROT_KP * rotError) + (EncoderNS::ROT_KD * derivativeRotError));

        unsigned long avgPulses = (diffLeft+diffRight)/2;
        unsigned long distanceError = targetCount - avgPulses;
        unsigned long derivativeDistanceError = distanceError - lastDistanceError;
        lastDistanceError = distanceError;

        int distanceAdjustment = int ((EncoderNS::DIST_KP*distanceError) + (EncoderNS::DIST_KD * derivativeDistanceError));


        int leftMotorSpeed = motorSpeed - rotAdjustment + distanceAdjustment;
        int rightMotorSpeed = motorSpeed + rotAdjustment + distanceAdjustment;
        o.displayCustom("Left motor:", leftMotorSpeed, "Adjustment:", adjustment);
        leftMotor.speed(leftMotorSpeed);
        rightMotor.speed(rightMotorSpeed);

        //delay to give motors time to change speeds
        delay(10);
    }

    //stop moving motors
    leftMotor.stop();
    rightMotor.stop();
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
    float correction = -22.0; // need decimal point for float value
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
    delay(250);
}
void Encoder::leftEncoderPulse(){
    leftEncoderPulses++;
}

void Encoder::rightEncoderPulse(){
    rightEncoderPulses++;
}

void Encoder::resetPulses(){
    leftEncoderPulses = 0;
    rightEncoderPulses = 0;
}