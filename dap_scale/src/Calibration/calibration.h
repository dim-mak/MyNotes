#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <SD.h>
#include "../Loadcells/loadCells.h"

const String CALIBRATION_FILE = "calibration.txt";

void performCalibration();
bool loadCalibration();
void saveCalibration();

#endif