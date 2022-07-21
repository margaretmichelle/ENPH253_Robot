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
#define LED_BUILTIN PB2
int ledState = LOW; 
unsigned long previousMillis = 0;
const long interval = 4000;

Robot::Master master;
OLED oledDisplay;

void setup()
{
    oledDisplay.start();

    pinMode(LED_BUILTIN, OUTPUT);

    master.setState(Robot::MasterState::ObstacleFollow); //Just for Testing Purposes 
}

void loop()
{
    //pwm_start(PA_10, DriveMotorPins::MOTOR_FREQ, 2100, RESOLUTION_12B_COMPARE_FORMAT);
    master.poll(oledDisplay, counter);
    counter++;

      unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    digitalWrite(LED_BUILTIN, ledState);
  }
};