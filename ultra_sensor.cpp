#include "ultra_sensor.h"

//Back Sensor Pins
#define BACK_TRIG 12
#define BACK_ECHO 11

//Side Sensor Pins
#define SIDE_TRIG 9
#define SIDE_ECHO 10

//Timeout prevents code from freezing if no echo is received
#define ULTRASONIC_TIMEOUT 30000UL //microseconds

void ultraInit() {
  pinMode(BACK_TRIG, OUTPUT);
  pinMode(BACK_ECHO, INPUT);

  pinMode(SIDE_TRIG, OUTPUT);
  pinMode(SIDE_ECHO, INPUT);
}

float measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH, ULTRASONIC_TIMEOUT);

  if(duration == 0) {
    return -1; //no valid reading
  }

  float distance = duration * 0.0343 / 2.0;
  return distance;
}

float readBackDistance() {
  return measureDistance(BACK_TRIG, BACK_ECHO);
}

float readSideDistance() {
  return measureDistance(SIDE_TRIG, SIDE_ECHO);
}