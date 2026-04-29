#ifndef ULTRA_H
#define ULTRA_H

#include <Arduino.h>

void ultraInit();

float readBackDistance();
float readSideDistance();

#endif