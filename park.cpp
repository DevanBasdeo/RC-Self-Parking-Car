#include "park.h"
#include "motor.h"
#include "servo.h"
#include "ir_sensor.h"
#include "ultra_sensor.h"

//Parking Gap Values
#define SIDE_LOW_THRESHOLD_CM 35
#define SIDE_GAP_THRESHOLD_CM 45

#define GAP_MIN_COUNT 8
#define END_CAR_CONFIRM_COUNT 2

//Speed Values
#define STRAIGHT_SPEED 100
#define TURNING_SPEED 140

//Time Values
#define REVERSE_AFTER_GAP_TIME_MS 400

#define FIRST_REVERSE_TIME_MS 1800
#define SECOND_REVERSE_TIME_MS 1800

#define BACK_SAFE_DISTANCE_CM 8

//Initialisation
void parkInit() {
  motorInit();
  steeringInit();
  IRSensorInit();
  ultraInit();

  Stop();
  centrePosition();
}

//Prevents Rear Collision
void reverseSafely(unsigned long reverseTime, int speedValue) {
  unsigned long startTime = millis();

  while (millis() - startTime < reverseTime) {
    float backDistance = readBackDistance();

    Serial.print("Back distance: ");
    Serial.println(backDistance);

    if (backDistance != -1 && backDistance <= BACK_SAFE_DISTANCE_CM) {
      Serial.println("Rear object too close - stopping reverse");
      Stop();
      return;
    }

    BackwardSpeed(speedValue);
    delay(20);
  }

  Stop();
}

//Parking Function
void Park() {
  int gapCount = 0;
  int endCarCount = 0;

  bool besideFirstCar = false;
  bool gapStarted = false;

  Stop();
  centrePosition();
  delay(700);

  //First Parking Phase: Find FIrst Car -> Measure Gap Count -> Find End Car
  while (true) {
    float sideDistance = readSideDistance();

    //Prints Readings for Debugging Purposes
    Serial.print("Side distance: ");
    Serial.print(sideDistance);
    Serial.print(" | First car: ");
    Serial.print(besideFirstCar);
    Serial.print(" | Gap started: ");
    Serial.print(gapStarted);
    Serial.print(" | Gap count: ");
    Serial.print(gapCount);
    Serial.print(" | End car count: ");
    Serial.println(endCarCount);

    ForwardSpeed(STRAIGHT_SPEED);

    //First Car Detection Code
    if (!besideFirstCar) {
      if (sideDistance != -1 && sideDistance < SIDE_LOW_THRESHOLD_CM) {
        besideFirstCar = true;
        Serial.println("First car detected");
      }
    }

    //Measuring Gap
    else if (!gapStarted) {
      if (sideDistance != -1 && sideDistance > SIDE_GAP_THRESHOLD_CM) {
        gapCount++;

        if (gapCount >= GAP_MIN_COUNT) {
          gapStarted = true;
          Serial.println("Parking gap started");
        }
      } else {
        gapCount = 0;
      }
    }

    //End Car Detection Code
    else {
      if (sideDistance != -1 && sideDistance < SIDE_LOW_THRESHOLD_CM) {
        endCarCount++;

        if (endCarCount >= END_CAR_CONFIRM_COUNT) {
          Serial.println("End car detected - stopping");
          Stop();
          break;
        }
      } else {
        endCarCount = 0;
      }
    }

    delay(120);
  }

  Stop();
  delay(700);

  //Reverse to Position Car for Parking
  Serial.println("Reversing slightly after gap detection");

  centrePosition();
  delay(300);

  reverseSafely(REVERSE_AFTER_GAP_TIME_MS, STRAIGHT_SPEED);

  Stop();
  delay(700);

  //Right Steering Reverse Code
  Serial.println("Turning right");

  turnRight();
  delay(1000);

  Serial.println("Reversing right");
  reverseSafely(FIRST_REVERSE_TIME_MS, TURNING_SPEED);

  Stop();
  delay(500);

  //Left Steering Reverse Code
  Serial.println("Turning left");

  turnLeft();
  delay(1000);

  Serial.println("Reversing left");
  reverseSafely(SECOND_REVERSE_TIME_MS, TURNING_SPEED);

  Stop();
  delay(500);

  //Stop and Straighten Wheels
  Serial.println("Centre steering");

  centrePosition();
  delay(700);

  //MOve Forward till IR Sensor Detects Car
  Serial.println("Final forward until IR detects");

  ForwardSpeed(STRAIGHT_SPEED);

  while (!IRRead()) {
    delay(20);
  }

  Stop();
  centrePosition();

  Serial.println("Park complete");
}