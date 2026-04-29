#ifndef SERVO_H
#define SERVO_H

#include <Arduino.h>

//Functions
void steeringInit();
void setSteeringPWM(int pwmValue);
void setSteering(float input); 

//Turning Functions
void turnLeft();
void turnRight();
void centrePosition();

#endif