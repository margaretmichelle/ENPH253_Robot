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

    /**
     * @brief A faster implementation of analogWrite.
     * 
     * @param pin A physical pin on the Blue Pill. Pin mode must be set to PWM on this
     *          pin before this method is called.
     * @param duty_cycle8 An 8-bit duty cycle (ex. 0 to 255 inclusive)
     */ 
    static void fastAnalogWrite(uint8_t pin, int duty_cycle8);

    /** 
     * @brief Sets all the timers to 20ms period. Ensures consistency between servos and motors on the same timer.
     */
    static void timerSetup();

    /**
     * @brief Regulate main loop time. Ensures that loopTime >=  Constants::LOOP_LENGTH)
     *
     * @param startTime the start time of the loop (from millis())
     *
     * @param endTime the end time of the loop (from millis())
     */
    static void regulateLoop(long startTime, long endTime);
};

#endif