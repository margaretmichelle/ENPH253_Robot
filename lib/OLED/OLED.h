#ifndef OLED_h
#define OLED_h

#include <PID.h>
#include <Arduino.h>

class OLED {

  public:

    // Constructor
    OLED();

    void start();

    void chooseState();

    bool stateChosen();

    int getState();

    /**
     * @brief Display screens on OLED to be switched with button and encoder
     */
    void displayScreen(int leftMotorSpeed, int rightMotorSpeed, int leftReflectance, int rightReflectance, int TL, int TR, int BL, int BR);

    /**
     * @brief Display tape following PID values with the ablility to change them
     */
    void displayTFPID();

    /**
     * @brief Display edge following PID values with the ablility to change them
     */
    void displayEdgePID();

    /**
     * @brief Display driving motor speeds
     */
    void displaySpeed(int leftMotorSpeed, int rightMotorSpeed);

    /**
     * @brief Display tape following reflectance sensor values
     */
    void displayTFReflectance(int leftReflectance, int rightReflectance);

    /**
     * @brief Display edge following PID reflectance sencor values
     */
    void displayEdgeReflectance(int TL, int TR, int BL, int BR);

    /**
     * @brief Display sonar distance sensor output in centimetres
     */
    void displayDistance(long distance);

    /**
     * @brief Display custom screen with one values and its label
     */
    void displayCustom(String label, int val);

    /**
     * @brief Display custom screen with two values and their labels
     */
    void displayCustom(String labelA, int valA, String labelB, int valB);

    // Getter methods
    
    int getTKP();
    int getTKI();
    int getTKD();

    int getEKP();
    int getEKI();
    int getEKD();
};

#endif