#ifndef Obstacle_h
#define Obstacle_h

#include <Constants.h>

class Obstacle {
    public:

        /**
        * @brief Construct a new Obstacle object
        * 
        * @param leftMotor 
        * @param rightMotor 
        * @param speed 
        */
        Obstacle(int trigger, int echo);

    
        void useObstacle();

        long getDistance() { return distance;}


    private:
        int trigPin;
        int echoPin;
        long duration;
        long distance;

        int motorSpeed;
};

#endif