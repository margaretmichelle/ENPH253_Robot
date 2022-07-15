#include <Arduino.h>
#include <Constants.h>
#include <OLED.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Helper.h>

void clicked();
void readEncoder();

int screen;
int KP;
int KI;
int KD;

Adafruit_SSD1306 display(OLEDDisplayNM::SCREEN_WIDTH, OLEDDisplayNM::SCREEN_HEIGHT, &Wire, OLEDDisplayNM::OLED_RESET);

OLED::OLED() {

  pinMode(OLEDDisplayNM::BUTTON_PIN, INPUT);
  pinMode(OLEDDisplayNM::CLK_PIN, INPUT);
  pinMode(OLEDDisplayNM::DT_PIN, INPUT);

  attachInterrupt(digitalPinToInterrupt(OLEDDisplayNM::BUTTON_PIN), clicked, RISING);
  attachInterrupt(digitalPinToInterrupt(OLEDDisplayNM::CLK_PIN), readEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(OLEDDisplayNM::DT_PIN), readEncoder, CHANGE);

  screen = 0;
  KP = 0;
  KI = 0;
  KD = 0;
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
    if (digitalRead(OLEDDisplayNM::CLK_PIN)) {
      if (digitalRead(OLEDDisplayNM::DT_PIN)) {
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
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);

  switch (screen) {
    case 0:
      display.setCursor(3,2);
      display.println("Robot");
      display.write(3);
      display.startscrollright(0x00, 0x07);
      break;
    case 1:
      display.setTextSize(2);
      display.setTextColor(BLACK, WHITE);
      display.println("KP: " + KP);
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.println("KI: " + KI);
      display.println("KD: " + KD);
      break;
    case 2:
      display.setTextSize(1);
      display.println("KP: " + KP);
      display.setTextSize(2);
      display.setTextColor(BLACK, WHITE);
      display.println("KI: " + KI);
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.println("KD: " + KD);
      break;
    case 3:
      display.setTextSize(1);
      display.println("KP: " + KP);
      display.setTextSize(1);
      display.println("KI: " + KI);
      display.setTextSize(2);
      display.setTextColor(BLACK, WHITE);
      display.println("KD: " + KD);
      break;
  }

  display.display();
}