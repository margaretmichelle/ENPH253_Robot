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
int page;
int TKP;
int TKI;
int TKD;

int EKP;
int EKI;
int EKD;

Adafruit_SSD1306 oled(OLEDDisplayNS::SCREEN_WIDTH, OLEDDisplayNS::SCREEN_HEIGHT, &Wire, OLEDDisplayNS::OLED_RESET);

OLED::OLED() {

  pinMode(OLEDDisplayNS::BUTTON_PIN, INPUT);
  pinMode(OLEDDisplayNS::CLK_PIN, INPUT);
  pinMode(OLEDDisplayNS::DT_PIN, INPUT);

  attachInterrupt(digitalPinToInterrupt(OLEDDisplayNS::BUTTON_PIN), clicked, RISING);
  attachInterrupt(digitalPinToInterrupt(OLEDDisplayNS::CLK_PIN), readEncoder, RISING);
  // attachInterrupt(digitalPinToInterrupt(OLEDDisplayNS::DT_PIN), readEncoder, CHANGE);

  screen = 0;
  page = 0;

  TKP = TapeFollowerNS::KP;
  TKI = TapeFollowerNS::KI;
  TKD = TapeFollowerNS::KD;

  EKP = EdgeFollowerNS::KP;
  EKI = EdgeFollowerNS::KI;
  EKD = EdgeFollowerNS::KD;
}

void OLED::start() {
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.display();
}

int OLED::getTKP() {
  return TKP;
}

int OLED::getTKI() {
  return TKI;
}

int OLED::getTKD() {
  return TKD;
}

int OLED::getEKP() {
  return EKP;
}

int OLED::getEKI() {
  return EKI;
}

int OLED::getEKD() {
  return EKD;
}

void clicked() {
  screen++;
    if (screen > 7) {
        screen = 0;
    }
}

void readEncoder() {
  if (screen != 0) {
    if (digitalRead(OLEDDisplayNS::CLK_PIN)) {
      if (digitalRead(OLEDDisplayNS::DT_PIN)) {
        switch (screen) {
          case 2:
            TKP++;
            break;
          case 3:
            TKI++;
            break;
          case 4:
            TKD++;
            break;
          case 5:
            EKP++;
            break;
          case 6:
            EKI++;
            break;
          case 7:
            EKD++;
            break;
          default:
            page++;
            if (page > 3) {
              page = 0;
            }
            break;
        }
        
      } else {
          switch (screen) {
            case 2:
              TKP--;
              break;
            case 3:
              TKI--;
              break;
            case 4:
              TKD--;
              break;
            case 5:
              EKP--;
              break;
            case 6:
              EKI--;
              break;
            case 7:
              EKD--;
              break;
            default:
              page--;
              if (page < 0) {
                page = 3;
              }
              break;
          }
      }
    }
  }
}

void OLED::displayScreen(int leftMotorSpeed, int rightMotorSpeed, int leftReflectance, int rightReflectance, int TL, int TR, int BL, int BR, long distance) {
  if (screen == 0) {
    oled.clearDisplay();
    oled.setTextColor(SSD1306_WHITE);
    oled.setTextSize(2);
    oled.setCursor(25,25);
    oled.print("Robot ");
    oled.write(3);
    
    oled.display();
  } else if (screen == 1) {
    switch (page) {
      case 0:
        displaySpeed(leftMotorSpeed, rightMotorSpeed);
        break;
      case 1:
        displayTFReflectance(leftReflectance, rightReflectance);
        break;
      case 2:
        displayEdgeReflectance(TL, TR, BL, BR);
        break;
      case 3:
        displayDistance(distance);
        break;
    }
  } else if (screen < 5) {
    displayTFPID();
  } else if (screen < 8) {
    displayEdgePID();
  }

}

void OLED::displayTFPID() {
  oled.clearDisplay();
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0,5);
  oled.setTextSize(1);
  oled.println("Tape Following PID:");
  oled.setCursor(0,17);
  oled.setTextSize(2);

  switch (screen) {
    case 2:
      oled.setTextColor(BLACK, WHITE);
      oled.print("KP: ");
      oled.print(TKP);
      oled.setTextColor(WHITE);
      oled.print("\nKI: ");
      oled.print(TKI);
      oled.print("\nKD: ");
      oled.print(TKD);
      break;
    case 3:
      oled.print("KP: ");
      oled.print(TKP);
      oled.setTextColor(BLACK, WHITE);
      oled.print("\nKI: ");
      oled.print(TKI);
      oled.setTextColor(WHITE);
      oled.print("\nKD: ");
      oled.print(TKD);
      break;
    case 4:
      oled.print("KP: ");
      oled.print(TKP);
      oled.print("\nKI: ");
      oled.print(TKI);
      oled.setTextColor(BLACK, WHITE);
      oled.print("\nKD: ");
      oled.print(TKD);
      break;
  }

  oled.display();
}

void OLED::displayEdgePID() {
  oled.clearDisplay();
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0,5);
  oled.setTextSize(1);
  oled.println("Edge Following PID:");
  oled.setCursor(0,17);
  oled.setTextSize(2);

  switch (screen) {
    case 5:
      oled.setTextColor(BLACK, WHITE);
      oled.print("KP: ");
      oled.print(EKP);
      oled.setTextColor(WHITE);
      oled.print("\nKI: ");
      oled.print(EKI);
      oled.print("\nKD: ");
      oled.print(EKD);
      break;
    case 6:
      oled.print("KP: ");
      oled.print(EKP);
      oled.setTextColor(BLACK, WHITE);
      oled.print("\nKI: ");
      oled.print(EKI);
      oled.setTextColor(WHITE);
      oled.print("\nKD: ");
      oled.print(EKD);
      break;
    case 7:
      oled.print("KP: ");
      oled.print(EKP);
      oled.print("\nKI: ");
      oled.print(EKI);
      oled.setTextColor(BLACK, WHITE);
      oled.print("\nKD: ");
      oled.print(EKD);
      break;
  }

  oled.display();
}

void OLED::displaySpeed(int leftMotorSpeed, int rightMotorSpeed) {
  oled.clearDisplay();
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0,5);
  oled.setTextSize(1);
  oled.println("Motor Speeds: ");
  oled.setCursor(0,17);
  oled.print("Left motor: ");
  oled.print(leftMotorSpeed);
  oled.print("\n\nRight motor: ");
  oled.print(rightMotorSpeed);

  oled.display();
}

void OLED::displayTFReflectance(int leftReflectance, int rightReflectance) {
  oled.clearDisplay();
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0,5);
  oled.setTextSize(1);
  oled.println("Tape Following:");
  oled.setCursor(0,17);
  oled.print("Left: ");
  oled.print(leftReflectance);
  oled.print("\n\nRight ");
  oled.print(rightReflectance);

  oled.display();
}

void OLED::displayEdgeReflectance(int TL, int TR, int BL, int BR) {
  oled.clearDisplay();
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0,5);
  oled.setTextSize(1);
  oled.println("Edge Detection:");
  oled.setCursor(20,17);
  oled.print(TL);
  oled.setCursor(90,17);
  oled.print(TR);
  oled.setCursor(20,50);
  oled.print(BL);
  oled.setCursor(90,50);
  oled.print(BR);

  oled.display();
}

void OLED::displayDistance(long distance) {
  oled.clearDisplay();
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0,5);
  oled.setTextSize(1);
  oled.println("Sonar Distance (cm): ");
  oled.setCursor(0,17);
  oled.println(distance);

  oled.display();
}

void OLED::displayCustom(String label, int val) {
  oled.clearDisplay();
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0,0);
  oled.setTextSize(1);
  oled.println(label);
  oled.println(val);

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