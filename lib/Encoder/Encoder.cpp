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

void Encoder::driveStraight(int distance, int motorPower){
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
    LeftMotor.stop();
    RightMotor.stop();
}

void leftEncoderPulse(){
    leftEncoderPulses++;
}

void rightEncoderPulse(){
    rightEncoderPulses++;
}