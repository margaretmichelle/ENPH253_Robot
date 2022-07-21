#ifndef OLED_h
#define OLED_h

#include <PID.h>
#include <Arduino.h>


class OLED {

  public:

    // Constructor
    OLED();

    void start();


    /**
     * @brief display screen on OLED
     */
    void displayScreen();

    void displayPID();

    void displaySpeed(int leftMotorSpeed, int rightMotorSpeed);

    void displayCustom(String labelA, int valA, String labelB, int valB);

    void displayDistance(long distance);

    int getKP();
    int getKI();
    int getKD();
};

#endif