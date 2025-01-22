#ifndef LOADCELLS_H
#define LOADCELLS_H

#include <HX711.h>
#include "../Utilities/utilities.h"

// Load cell setup
extern HX711 scale1, scale2, scale3;
extern bool thirdLoadCellConnected;

// Pins
const int DT1 = 6, SCK1 = 9;
const int DT2 = 7, SCK2 = 10;
const int DT3 = 8, SCK3 = 11;

// Calibration Factors
extern float calibrationFactor1;
extern float calibrationFactor2;
extern float calibrationFactor3;

void initLoadCells();
void tareAllLoadCells();
void updateLoadCellState();
float getWeight1();
float getWeight2();
float getWeight3();
bool isThirdLoadCellConnected();

#endif