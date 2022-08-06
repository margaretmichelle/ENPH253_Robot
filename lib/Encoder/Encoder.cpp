#include <Arduino.h>
#include <Constants.h>
#include <Encoder.h>
#include <Motor.h>

void leftEncoderPulse();
void rightEncoderPulse();

long int leftEncoderPulses;
long int rightEncoderPulses;

Motor leftMotor(MasterNS::LEFT_MOTOR_PIN_1, MasterNS::LEFT_MOTOR_PIN_2);
Motor rightMotor(MasterNS::RIGHT_MOTOR_PIN_1, MasterNS::RIGHT_MOTOR_PIN_2);

Encoder::Encoder(){
    pinMode(EncoderNS::LEFT_MOTOR_ENCODER_PIN, INPUT);
    pinMode(EncoderNS::RIGHT_MOTOR_ENCODER_PIN, INPUT);

    attachInterrupt(digitalPinToInterrupt(EncoderNS::LEFT_MOTOR_ENCODER_PIN), leftEncoderPulse, RISING);
    attachInterrupt(digitalPinToInterrupt(EncoderNS::RIGHT_MOTOR_ENCODER_PIN), rightEncoderPulse, RISING);

    leftEncoderPulses = 0;
    rightEncoderPulses = 0;
}

void Encoder::driveStraight(float distance, int motorPower){
    // Set inital motor powers
    int leftPower = motorPower;
    int rightPower = motorPower;

    // Sets target number of counts for the encoder
    float numOfRevs = distance / EncoderNS::ROTATION_DISTANCE_MM;
    unsigned long targetCount = numOfRevs * EncoderNS::PULSES_PER_ROTATION;

    // Sets inital encoder counts to keep track of new changes to encoder counts
    unsigned long initalLeftCount = leftEncoderPulses;
    unsigned long initalRightCount = rightEncoderPulses;

    //travels until one wheel reaches the end
    while ( (leftEncoderPulses - initalLeftCount) < targetCount && rightEncoderPulses - initalRightCount < targetCount ){
        // Chooses a sample count, have to do it this way since the interupted value will constantly change
        unsigned long currentLeftCount = leftEncoderPulses;
        unsigned long currentRightCount = rightEncoderPulses;

        //Looks at the change in encoder pulses from the initial code to see what motor needs to travel more
        unsigned long diffLeft = currentLeftCount - initalLeftCount;
        unsigned long diffRight = currentRightCount - initalRightCount;

        //Some code I found online uses this I wanted to test out mine first, IDK why they do it this way
        /*
        unsigned long diffLeft = currentLeftCount - prevLeftCount;
        unsigned long diffRight = currentRightCount - prevRightCount;

        unsigned long prevLeftCount = currentLeftCount;
        unsigned long prevRightCount = currentRightCount;
        */

        //Increase left's speed if right has travelled more
        if (diffLeft < diffRight){
            rightPower -= EncoderNS::POWER_OFFSET;
            leftPower += EncoderNS::POWER_OFFSET;
        }

        //Increase right's speed if left has travelled more
        else if(diffLeft > diffRight){
            rightPower += EncoderNS::POWER_OFFSET;
            leftPower -= EncoderNS::POWER_OFFSET;
        }

        leftMotor.speed(leftPower);
        rightMotor.speed(rightPower);

        //delay to give motors time to change speeds
        delay(20);
    }

    //stop moving motors
    leftMotor.stop();
    rightMotor.stop();
}

void pivotAngle(float angleDegrees) {
// use wheel encoders to pivot (turn) by specified angle

    // set motor speed for pivoting
    int speed = EncoderNS::PIVOT_WHEEL_SPEED; // clockwise
    int angle = angleDegrees;

    if (angleDegrees < 0) {
        speed *= -1; 
    }

    // use correction to improve angle accuracy
    // adjust correction value based on test results
    float correction = -2.0; // need decimal point for float value
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
void leftEncoderPulse(){
    leftEncoderPulses++;
}

void rightEncoderPulse(){
    rightEncoderPulses++;
}