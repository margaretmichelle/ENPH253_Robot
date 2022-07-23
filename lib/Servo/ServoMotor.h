#ifndef servomotor_h
#define servomotor_h

class ServoMotor {
  public:
    // Constructor
    ServoMotor(int controlPin);

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
    
  private:
    int currentPos;
    PinName pinName;

    int mapAngleToDutyCycle(int angle);
};

#endif