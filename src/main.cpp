#include <Arduino.h>
#include <Constants.h>
#include <OLED.h>
#include <Wire.h>
#include <Robot.h> 
#include <Encoder.h>

#define LED_BUILTIN PB2
int ledState = LOW; 
unsigned long previousMillis = 0;
const long interval = 500;

Robot::Master master;
OLED oledDisplay;

void useEdgeDetection();
void slaveInterrupt();

void setup() {
    oledDisplay.start();

    pinMode(LED_BUILTIN, OUTPUT);

    //Attach interrupts to the back edge detection
    attachInterrupt(digitalPinToInterrupt(EdgeFollowerNS::BOTTOM_LEFT_SENSOR_PIN), useEdgeDetection, RISING);
    attachInterrupt(digitalPinToInterrupt(EdgeFollowerNS::BOTTOM_RIGHT_SENSOR_PIN), useEdgeDetection, RISING);

    attachInterrupt(digitalPinToInterrupt(PA2), slaveInterrupt, RISING);

    master.setState(Robot::MasterState::EdgeFollow);

    while (!oledDisplay.stateChosen()) {
      oledDisplay.chooseState();
      if (oledDisplay.stateChosen()) {
        master.setState((Robot::MasterState) oledDisplay.getState()); //Just for Testing Purposes
        delay(1000);
      }
    }
}

void loop() {
  // master.poll(oledDisplay);
  oledDisplay.displayScreen(1,2,3,4,5,6,7,8);

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

void slaveInterrupt() {
  master.changeSlaveState();
}