#include "motor.h"


#define ENA 5
#define IN1 6
#define IN2 7

#define MAX_SPEED 255
#define MIN_SPEED 0

int currentSpeed = 100;

//Clamp
int clampSpeed(int speedValue) {
  if (speedValue < MIN_SPEED) return MIN_SPEED;
  if (speedValue > MAX_SPEED) return MAX_SPEED;
  return speedValue;
}

//Initialisation
void motorInit() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);

  currentSpeed = 100;
}

//Movement Code
//Anticlockwise = Forward Movement
void Forward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, currentSpeed);
}

//Clockwise = Backward Movement
void Backward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, currentSpeed);
}

//Stop Car
void Stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
}

//Speed Control
void setSpeed(int speedValue) {
  currentSpeed = clampSpeed(speedValue);
}

//Speed + Movement Control
void ForwardSpeed(int speedValue) {
  currentSpeed = clampSpeed(speedValue);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, currentSpeed);
}

void BackwardSpeed(int speedValue) {
  currentSpeed = clampSpeed(speedValue);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, currentSpeed);
}