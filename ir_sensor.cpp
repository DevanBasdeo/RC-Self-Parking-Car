#include "ir_sensor.h"

#define IR_PIN 8

//Initialisation
void IRSensorInit() {
  pinMode(IR_PIN, INPUT);
}

//Read Sensor
int IRRead() {
  int state = digitalRead(IR_PIN);


  //Object Detection
  if (state == LOW) {
    return 1;
  } else {
    return 0;
  }
}