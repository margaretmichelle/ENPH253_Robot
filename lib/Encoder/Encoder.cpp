#include <Arduino.h>
#include <Constants.h>
#include <Encoder.h>
#include <Motor.h>

void leftEncoderPulse();
void rightEncoderPulse();

long int leftEncoderPulses;
long int rightEncoderPulses;

Motor LeftMotor(MasterNS::LEFT_MOTOR_PIN_1, MasterNS::LEFT_MOTOR_PIN_2);
Motor RightMotor(MasterNS::RIGHT_MOTOR_PIN_1, MasterNS::RIGHT_MOTOR_PIN_2);

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

    float numOfRevs = distance / EncoderNS::ROTATION_DISTANCE_MM;
    unsigned long targetCount = numOfRevs * EncoderNS::PULSES_PER_ROTATION;

    unsigned long initalLeftCount = leftEncoderPulses;
    unsigned long initalRightCount = rightEncoderPulses;

    unsigned long prevLeftCount = leftEncoderPulses;
    unsigned long prevRightCount = rightEncoderPulses;

    while ( (leftEncoderPulses - initalLeftCount) < targetCount && rightEncoderPulses - initalRightCount < targetCount ){
        unsigned long currentLeftCount = leftEncoderPulses;
        unsigned long currentRightCount = rightEncoderPulses;

        unsigned long diffLeft = currentLeftCount - initalLeftCount;
        unsigned long diffRight = currentRightCount - initalRightCount;

        //unsigned long diffLeft = currentLeftCount - prevLeftCount;
        //unsigned long diffRight = currentRightCount - prevRightCount;

        //unsigned long prevLeftCount = currentLeftCount;
        //unsigned long prevRightCount = currentRightCount;

        if (diffLeft < diffRight){
            rightPower -= EncoderNS::POWER_OFFSET;
            leftPower += EncoderNS::POWER_OFFSET;
        }
        else if(diffLeft > diffRight){
            rightPower += EncoderNS::POWER_OFFSET;
            leftPower -= EncoderNS::POWER_OFFSET;
        }

        delay(20);
    }

    LeftMotor.stop();
    RightMotor.stop();
}

void leftEncoderPulse(){
    leftEncoderPulses++;
}

void rightEncoderPulse(){
    rightEncoderPulses++;
}