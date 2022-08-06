#ifndef servomotor_h
#define servomotor_h

class ServoMotor {
  public:
    // Constructor
    ServoMotor(int controlPin);

    /**
     * @brief setup the servo to its starting position
     */
    void setupServo(int angle);

    /**
     * @brief write the servo position
     */
    void write(int angle);

    /**
     * @brief get servo position
     */
    int getPosition() {
        return currentPos;
    }

    void stop();
    
  private:
    int currentPos;
    PinName pinName;

    int mapAngleToPulseWidth(int angle);
};

#endif