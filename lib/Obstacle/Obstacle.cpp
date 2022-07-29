#include <Obstacle.h>
#include <Constants.h>

Obstacle::Obstacle(int trigger, int echo) {
//set-up pinmodes
    trigPin = trigger;
    echoPin = echo;
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}


void Obstacle::useObstacle() {

    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2); 
    digitalWrite(trigPin, HIGH); 
    delayMicroseconds(10); 

    digitalWrite(trigPin, LOW); 
    duration = pulseIn(echoPin, HIGH); 
    distance = duration / 58.2; //distance in cm 
    delay(50); // what is the delay for?
}

