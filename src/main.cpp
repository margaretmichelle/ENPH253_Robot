#include <Arduino.h>
#include <Constants.h>
#include <Motor.h>
#include <PID.h>
#include <Helper.h>
#include <IR.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Robot.h> 

#define LED_BUILTIN PB2
int ledState = LOW; 
unsigned long previousMillis = 0;
const long interval = 2500;

Robot::Master master;
OLED oledDisplay;

void useEdgeDetection();

void setup()
{
    oledDisplay.start();

    pinMode(LED_BUILTIN, OUTPUT);

    //Attach interrupts to the back edge detection
    attachInterrupt(EdgeFollowerNS::BOTTOM_LEFT_SENSOR_PIN, useEdgeDetection, RISING);
    attachInterrupt(EdgeFollowerNS::BOTTOM_RIGHT_SENSOR_PIN, useEdgeDetection, RISING);

    master.setState(Robot::MasterState::TapeFollow); //Just for Testing Purposes 
}

void loop()
{
    //pwm_start(PA_10, DriveMotorPins::MOTOR_FREQ, 2100, RESOLUTION_12B_COMPARE_FORMAT);
    master.poll(oledDisplay);

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

void useEdgeDetection() {
    master.useEdgeDetection();
}