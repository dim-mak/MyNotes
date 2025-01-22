#ifndef LOGGING_H
#define LOGGING_H

#include <SD.h>
#include "../Utilities/utilities.h"

String getNextLogFileName();
void logData(const String &fileName, float weight1, float weight2, float weight3, unsigned long startTime, LiquidCrystal &lcd);

#endif