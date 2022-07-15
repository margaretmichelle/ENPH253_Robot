#ifndef motor_h
#define motor_h

class Motor {
  public:
    // Constructor
    Motor(int pin1, int pin2);

    /**
     * @brief write the motor speed to be 0
     */
    void stop();

    /**
     * @brief set motor to a certain speed
     * 
     * @param speed int between 0 to 255 inclusive
     */
    void speed(int speed);
    
  private:
    int pin1;
    int pin2;
    int previousSpeed;
    PinName pinName1;
    PinName pinName2;
};

#endif