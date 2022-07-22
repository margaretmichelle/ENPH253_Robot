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
const long interval = 2500;

Robot::Master master;
OLED oledDisplay;

void useEdgeDetection();

void setup()
{
    oledDisplay.start();

    pinMode(LED_BUILTIN, OUTPUT);
    
    pinMode(EdgeFollowerNS::BOTTOM_LEFT_SENSOR_PIN, INPUT_PULLUP); //we already do this in the class
    pinMode(EdgeFollowerNS::BOTTOM_RIGHT_SENSOR_PIN, INPUT_PULLUP);
    //Attach interrupts to the back edge detection
    attachInterrupt(EdgeFollowerNS::BOTTOM_LEFT_SENSOR_PIN, useEdgeDetection, RISING);
    attachInterrupt(EdgeFollowerNS::BOTTOM_RIGHT_SENSOR_PIN, useEdgeDetection, RISING);

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

void useEdgeDetection() {
    master.useEdgeDetection();
}