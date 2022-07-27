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
#include <ServoMotor.h>
#include <Claw.h>

#define LED_BUILTIN PB2
int ledState = LOW; 
unsigned long previousMillis = 0;
const long interval = 2500;

Robot::Master master;
OLED oledDisplay;

void useEdgeDetection();

void setup() {
    oledDisplay.start();

    pinMode(LED_BUILTIN, OUTPUT);

    //Attach interrupts to the back edge detection
    attachInterrupt(EdgeFollowerNS::BOTTOM_LEFT_SENSOR_PIN, useEdgeDetection, RISING);
    attachInterrupt(EdgeFollowerNS::BOTTOM_RIGHT_SENSOR_PIN, useEdgeDetection, RISING);

    master.setState(Robot::MasterState::IRFollow); //Just for Testing Purposes 
}

void loop() {
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
}

void useEdgeDetection() {
    master.useEdgeDetection();
}