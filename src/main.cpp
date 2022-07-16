#include <Arduino.h>
#include <Constants.h>
#include <Motor.h>
#include <PID.h>
#include <Helper.h>
// #include <IR.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Robot.h> 

int counter = 0;


Robot::Master master;
OLED oledDisplay;

void setup()
{
    oledDisplay.start();

    master.setState(Robot::MasterState::TapeFollow);
}

void loop()
{
    master.poll(oledDisplay, counter);
    counter++;
};