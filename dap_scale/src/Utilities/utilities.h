#ifndef UTILITIES_H
#define UTILITIES_H

#include <Arduino.h>
#include <LiquidCrystal.h>

String adjustPrecision(float weight);
void displayWeights(LiquidCrystal &lcd, float w1, float w2, float w3, bool logging);
void centerMessage(LiquidCrystal &lcd, const char *message);

#endif