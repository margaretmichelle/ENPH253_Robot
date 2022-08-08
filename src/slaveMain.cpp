// #include <Arduino.h>
// #include <Constants.h>
// #include <Motor.h>
// #include <PID.h>
// #include <Helper.h>
// #include <IR.h>
// #include <Wire.h>
// #include <Adafruit_SSD1306.h>
// #include <Wire.h>
// #include <Robot.h> 
// #include <ServoMotor.h>
// #include <Claw.h>

// #define LED_BUILTIN PB2

// int ledState = LOW; 
// unsigned long previousMillis = 0;
// const long interval = 2500;

// Robot::Slave slave;

// void slavePoll();

// void setup() {
//     pinMode(LED_BUILTIN, OUTPUT);

//     attachInterrupt(digitalPinToInterrupt(SlaveNS::BP_COMM_IN), slavePoll, RISING);
//     slave.setState(Robot::SlaveState::ClawActivateIdolOne); //Just for Testing Purposes 
// }

// void loop() {
//     unsigned long currentMillis = millis();

//   if (currentMillis - previousMillis >= interval) {
//     previousMillis = currentMillis;

//     if (ledState == LOW) {
//       ledState = HIGH;
//     } else {
//       ledState = LOW;
//     }

//     digitalWrite(LED_BUILTIN, ledState);
//   }
// }
 
// void slavePoll() {
//     digitalWrite(SlaveNS::BP_COMM_OUT, HIGH);
//     slave.poll();
// }

