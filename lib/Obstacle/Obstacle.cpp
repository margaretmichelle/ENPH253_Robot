#include <Obstacle.h>
#include <Constants.h>

Obstacle::Obstacle() {
//set-up pinmodes
    pinMode(ObstacleNS::TRIGPIN, OUTPUT);
    pinMode(ObstacleNS::ECHO_PIN, INPUT);
}


void Obstacle::useObstacle() {

    digitalWrite(ObstacleNS::TRIGPIN, LOW); 
    delayMicroseconds(2); 
    digitalWrite(ObstacleNS::TRIGPIN, HIGH); 
    delayMicroseconds(10); 

    digitalWrite(ObstacleNS::TRIGPIN, LOW); 
    duration = pulseIn(ObstacleNS::ECHO_PIN, HIGH); 
    distance = duration / 58.2; //distance in cm 
    delay(50);
}

