#include <Arduino.h>
#include <Constants.h>
#include <OLED.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Helper.h>
#include <PID.h>

void clicked();
void readEncoder();

int screen;
int KP;
int KI;
int KD;

Adafruit_SSD1306 oled(OLEDDisplayNS::SCREEN_WIDTH, OLEDDisplayNS::SCREEN_HEIGHT, &Wire, OLEDDisplayNS::OLED_RESET);

OLED::OLED() {

  pinMode(OLEDDisplayNS::BUTTON_PIN, INPUT);
  pinMode(OLEDDisplayNS::CLK_PIN, INPUT_PULLUP);
  pinMode(OLEDDisplayNS::DT_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(OLEDDisplayNS::BUTTON_PIN), clicked, RISING);
  attachInterrupt(digitalPinToInterrupt(OLEDDisplayNS::CLK_PIN), readEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(OLEDDisplayNS::DT_PIN), readEncoder, CHANGE);

  screen = 0;
  KP = 15;
  KI = 0;
  KD = 2;
}

void OLED::start() {
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.display();
}

int OLED::getKP() {
  return KP;
}

int OLED::getKI() {
  return KI;
}

int OLED::getKD() {
  return KD;
}

void clicked() {
  screen++;
    if (screen == 4) {
        screen = 0;
    }
}

void readEncoder() {
  if (screen != 0) {
    if (digitalRead(OLEDDisplayNS::CLK_PIN)) {
      if (digitalRead(OLEDDisplayNS::DT_PIN)) {
        switch (screen) {
          case 1:
            KP++;
            break;
          case 2:
            KI++;
            break;
          case 3:
            KD++;
            break;
        }
        
      } else {
          switch (screen) {
            case 1:
              KP--;
              break;
            case 2:
              KI--;
              break;
            case 3:
              KD--;
              break;
          }
      }
    }
  }
}

void OLED::displayScreen() {
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0,0);

  switch (screen) {
    case 0:
      oled.setCursor(30,30);
      oled.print("Robot ");
      oled.write(3);
      break;
    case 1:
      oled.setTextColor(BLACK, WHITE);
      oled.println("KP: " + KP);
      oled.setTextColor(WHITE);
      oled.println("KI: " + KI);
      oled.println("KD: " + KD);
      break;
    case 2:
      oled.println("KP: " + KP);
      oled.setTextColor(BLACK, WHITE);
      oled.println("KI: " + KI);
      oled.setTextColor(WHITE);
      oled.println("KD: " + KD);
      break;
    case 3:
      oled.println("KP: " + KP);
      oled.println("KI: " + KI);
      oled.setTextColor(BLACK, WHITE);
      oled.println("KD: " + KD);
      break;
  }

  oled.display();
}

void OLED::displayPID() {
  oled.clearDisplay();
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0,5);
  oled.setTextSize(1);
  oled.println("Tape Following PID:");
  oled.setCursor(0,17);
  oled.setTextSize(2);
  oled.print("KP: ");
  oled.print(KP);
  oled.print("\nKI: ");
  oled.print(KI);
  oled.print("\nKD: ");
  oled.print(KD);

  oled.display();
}

void OLED::displaySpeed(int leftMotorSpeed, int rightMotorSpeed) {
  oled.clearDisplay();
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0,0);
  oled.setTextSize(1);
  oled.println("Left motor speed: ");
  oled.println(leftMotorSpeed);
  oled.println("\nRight motor speed: ");
  oled.println(rightMotorSpeed);

  oled.display();
}

void OLED::displayCustom(String labelA, int valA, String labelB, int valB) {
  oled.clearDisplay();
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0,0);
  oled.setTextSize(1);
  oled.println(labelA);
  oled.println(valA);
  oled.println("\n" + labelB);
  oled.println(valB);

  oled.display();
}

void OLED::displayDistance(long distance) {
  oled.clearDisplay();
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0,0);
  oled.setTextSize(1);
  oled.println("distance (cm): ");
  oled.println(distance);

  oled.display();
}