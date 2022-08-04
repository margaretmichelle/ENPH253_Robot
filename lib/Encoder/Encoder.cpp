#include <Arduino.h>
#include <Constants.h>
#include <Encoder.h>
#include <Motor.h>

void leftEncoderPulse();
void rightEncoderPulse();

int leftEncoderPulses;
int rightEncoderPulses;

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

void Encoder::driveStraight(int distance){

}

void leftEncoderPulse(){
    leftEncoderPulses++;
}

void rightEncoderPulse(){
    rightEncoderPulses++;
}