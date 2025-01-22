#include "loadCells.h"

HX711 scale1, scale2, scale3;
bool thirdLoadCellConnected = false;
float calibrationFactor1 = 1.0;
float calibrationFactor2 = 1.0;
float calibrationFactor3 = 1.0;

void initLoadCells() {
  scale1.begin(DT1, SCK1);
  Serial.println(scale1.is_ready());
  scale2.begin(DT2, SCK2);
  Serial.println(scale2.is_ready());
  scale3.begin(DT3, SCK3);
  Serial.println(scale3.is_ready());
  thirdLoadCellConnected = scale3.is_ready();
}

void tareAllLoadCells() {
  scale1.tare();
  scale2.tare();
  if (thirdLoadCellConnected) {
    scale3.tare();
  }
}

void updateLoadCellState() {
  thirdLoadCellConnected = scale3.is_ready();
}

float getWeight1() {
  return scale1.get_units(10) / calibrationFactor1;
}

float getWeight2() {
  return scale2.get_units(10) / calibrationFactor2;
}

float getWeight3() {
  return scale3.get_units(10) / calibrationFactor3;
}

bool isThirdLoadCellConnected() {
  return thirdLoadCellConnected;
}