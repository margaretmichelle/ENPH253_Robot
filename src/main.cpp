#include <Arduino.h>
#include <Constants.h>
#include <OLED.h>
#include <Wire.h>
#include <Robot.h> 

#define LED_BUILTIN PC13
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

    master.setState(Robot::MasterState::Random);

    // while (!oledDisplay.stateChosen()) {
    //   oledDisplay.chooseState();
    //   if (oledDisplay.stateChosen()) {
    //     master.setState((Robot::MasterState) oledDisplay.getState()); //Just for Testing Purposes
    //     delay(1000);
    //   }
    // }
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
};

void useEdgeDetection() {
    master.useEdgeDetection();
}