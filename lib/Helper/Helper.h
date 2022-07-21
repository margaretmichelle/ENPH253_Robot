#ifndef Helper_H
#define Helper_H
#include <Arduino.h>
#include <Motor.h>
#include <Constants.h>

enum class Side {
  Left,
  Right
};

class Helper {
  public:

    /**
     * @brief Get average sensor readings value from analogPin. Average over numReadings samples
     *
     * @param analogPin analog pin number for reading
     * @param numReadings number of readings for average (must be >0)
     *
     * @return int which is the average sensor value
     */
    static int getAverageAnalogValue(int analogPin, int numReadings);
};

#endif