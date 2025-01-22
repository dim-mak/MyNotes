#include "logging.h"

String getNextLogFileName() {
  int fileIndex = 1;
  String fileName;
  do {
    fileName = "data" + String(fileIndex++) + ".txt";
  } while (SD.exists(fileName.c_str()));
  return fileName;
}

void logData(const String &fileName, float weight1, float weight2, float weight3, unsigned long startTime, LiquidCrystal &lcd) {
  File logFile = SD.open(fileName.c_str(), FILE_WRITE);
  if (logFile) {
    unsigned long relativeTime = millis() - startTime;
    logFile.print(relativeTime);
    logFile.print(" ms - LC_1:");
    logFile.print(weight1, 3);
    logFile.print(", LC_2:");
    logFile.print(weight2, 3);
    logFile.print(", LC_3:");
    logFile.println(isnan(weight3) ? "N/A" : String(weight3, 3));
    logFile.close();
  } else {
    Serial.println("SD Write Error!");
    centerMessage(lcd, "SD Write Error!");
  }
}
