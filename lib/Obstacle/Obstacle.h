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
        Obstacle();

    
        void useObstacle();

        long getDistance() { return distance;}


    private:
        long duration;
        long distance;

        int motorSpeed;
};

#endif