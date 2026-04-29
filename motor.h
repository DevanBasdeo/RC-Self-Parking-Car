#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

//Init
void motorInit();

//Basic control
void Forward();
void Backward();
void Stop();

//Speed control
void setSpeed(int speedValue);
void ForwardSpeed(int speedValue);
void BackwardSpeed(int speedValue);

#endif