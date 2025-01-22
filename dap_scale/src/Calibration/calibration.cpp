#include "calibration.h"

void performCalibration() {
  Serial.println("Starting Calibration...");
  tareAllLoadCells();

  Serial.println("Place a known weight on Load Cell 1 and enter its value (kg):");
  while (!Serial.available());
  float weight1 = Serial.parseFloat();
  calibrationFactor1 = scale1.get_units(10) / weight1;

  Serial.println("Place a known weight on Load Cell 2 and enter its value (kg):");
  while (!Serial.available());
  float weight2 = Serial.parseFloat();
  calibrationFactor2 = scale2.get_units(10) / weight2;

  if (thirdLoadCellConnected) {
    Serial.println("Place a known weight on Load Cell 3 and enter its value (kg):");
    while (!Serial.available());
    float weight3 = Serial.parseFloat();
    calibrationFactor3 = scale3.get_units(10) / weight3;
  }

  saveCalibration();
  Serial.println("Calibration Complete!");
}

bool loadCalibration() {
  File file = SD.open(CALIBRATION_FILE.c_str());
  if (file) {
    calibrationFactor1 = file.parseFloat();
    calibrationFactor2 = file.parseFloat();
    calibrationFactor3 = file.parseFloat();
    file.close();
    return true;
  }
  return false;
}

void saveCalibration() {
  File file = SD.open(CALIBRATION_FILE.c_str(), FILE_WRITE);
  if (file) {
    file.println(calibrationFactor1);
    file.println(calibrationFactor2);
    file.println(calibrationFactor3);
    file.close();
  }
}
