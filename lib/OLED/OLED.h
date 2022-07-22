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
    void displayScreen(int leftMotorSpeed, int rightMotorSpeed, int leftReflectance, int rightReflectance, int TL, int TR, int BL, int BR, long distance);

    void displayTFPID();

    void displayEdgePID();

    void displaySpeed(int leftMotorSpeed, int rightMotorSpeed);

    void displayTFReflectance(int leftReflectance, int rightReflectance);

    void displayEdgeReflectance(int TL, int TR, int BL, int BR);

    void displayDistance(long distance);

    void displayCustom(String labelA, int valA, String labelB, int valB);

    int getTKP();
    int getTKI();
    int getTKD();

    int getEKP();
    int getEKI();
    int getEKD();
};

#endif