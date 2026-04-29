#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "servo.h"


extern Adafruit_PWMServoDriver pwm;


#define SERVO_PIN    4
#define SERVO_CENTRE 320
#define SERVO_RIGHT  220
#define SERVO_LEFT   420

#define STEP_DELAY 15
#define STEP_SIZE  2

int currentPos = SERVO_CENTRE;

//Clamps Values to Prevent Over-Steering
int clampPWM(int value) {
  if (value < SERVO_RIGHT) return SERVO_RIGHT;
  if (value > SERVO_LEFT)  return SERVO_LEFT;
  return value;
}

//Initialisation
void steeringInit() {
  currentPos = SERVO_CENTRE;
  pwm.setPWM(SERVO_PIN, 0, currentPos);
}

//Allows User to Set Steering Value
void setSteeringPWM(int pwmValue) {
  currentPos = clampPWM(pwmValue);
  pwm.setPWM(SERVO_PIN, 0, currentPos);
}

//Maps app input values into servo PWM values
void setSteering(float input) {
  int pwmValue;

  if (input >= 0) {
    pwmValue = SERVO_CENTRE + input * (SERVO_LEFT - SERVO_CENTRE);
  } else {
    pwmValue = SERVO_CENTRE + input * (SERVO_CENTRE - SERVO_RIGHT);
  }

  setSteeringPWM(pwmValue);
}

//Increment for Smooth Control
void moveTo(int target) {
  target = clampPWM(target);

  while (currentPos != target) {
    if (currentPos < target) {
      currentPos += STEP_SIZE;
    } else {
      currentPos -= STEP_SIZE;
    }

    pwm.setPWM(SERVO_PIN, 0, currentPos);
    delay(STEP_DELAY);
  }
}

//Full Turn Functions
void turnRight() {
  moveTo(SERVO_RIGHT);
}

void turnLeft() {
  moveTo(SERVO_LEFT);
}

void centrePosition() {
  moveTo(SERVO_CENTRE);
}