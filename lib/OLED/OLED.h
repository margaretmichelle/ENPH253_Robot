#ifndef OLED_h
#define OLED_h

#include <Arduino.h>
#include <PID.h>

class OLED {

  public:

    // Constructor
    OLED();

    /**
     * @brief display screen on OLED
     */
    void displayScreen();

    int getKP();
    int getKI();
    int getKD();
};

#endif