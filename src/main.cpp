#include <Arduino.h>
#include <Constants.h>
#include <Motor.h>
#include <PID.h>
#include <Helper.h>
// #include <IR.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Robot.h> 


Robot::Master master;

void setup()
{
    master.setState(Robot::MasterState::TapeFollow);
}

void loop()
{
    master.poll();
};