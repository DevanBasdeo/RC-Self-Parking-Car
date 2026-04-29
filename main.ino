#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include "motor.h"
#include "servo.h"
#include "ir_sensor.h"
#include "ultra_sensor.h"
#include "park.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

SoftwareSerial BT(2, 3); // Arduino RX, TX

void setup() {
  Serial.begin(115200);
  BT.begin(9600);

  //Initialisation Codes
  pwm.begin();
  pwm.setPWMFreq(50);
  steeringInit();
  motorInit();
  IRSensorInit();
  ultraInit();
  parkInit();


  Serial.println("Bluetooth control ready");
}

void loop() {
  readBluetoothCommands();


}

void readBluetoothCommands() {
  while (BT.available()) {
    char c = BT.read();

    //Forward Motion of Car via App
    if (c == 'F') {
      Serial.println("Forward");
      Forward();      
    }

    //Reverse Car via App
    else if (c == 'B') {
      Serial.println("Backward");
      Backward();     
    }

    //Stop Car via App
    else if (c == 'S') {
      Serial.println("Stop");
      Stop();          
    }

    //Park Car via App
    else if (c == 'P') {
      Serial.println("Park");
      Park();     
    }

    //Turn Wheels via App
    else if (c == 'T') {
      delay(5);

      String value = "";

      while (BT.available()) {
        char nextChar = BT.peek();

        if (isDigit(nextChar)) {
          value += (char)BT.read(); //Ensures correct values are communicated to turn weels
        } else {
          break;
        }
      }

      int steeringValue = value.toInt();

      Serial.print("Steering: ");
      Serial.println(steeringValue);

      setSteeringPWM(steeringValue);  
    }
  }
}