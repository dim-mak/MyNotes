#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "src/LoadCells/loadcells.h"
#include "src/Logging/logging.h"
#include "src/Calibration/calibration.h"
#include "src/Utilities/utilities.h"

const int CHIP_SELECT_PIN = 53;

// LCD setup
const int rs = A3, en = A5, d4 = A9, d5 = A10, d6 = A11, d7 = A12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Buttons
const int zeroLeftButton = 2;
const int logRightButton = 3;

// Variables
bool logging = false;
unsigned long startTime = 0;
String logFileName;

void setup() {

  pinMode(A14, OUTPUT);
  pinMode(A13, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A1, OUTPUT);
  digitalWrite(A14, LOW);
  digitalWrite(A13, HIGH);
  digitalWrite(A4, LOW);
  digitalWrite(A0, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A1, HIGH);

  Serial.begin(9600);

  // Initialize LCD
  lcd.begin(20, 4);
  Serial.println("Initializing...");
  centerMessage(lcd, "Initializing...");
  delay(1000);
  lcd.clear();

  // Initialize load cells
  initLoadCells();

  // Initialize SD card
  if (!SD.begin(CHIP_SELECT_PIN)) {
    centerMessage(lcd, "SD Card Error!");
    Serial.println("SD Card Error!");
  }

  // Check third load cell
  updateLoadCellState();

  // Ask for calibration or normal mode
  Serial.println("Press 1 for Calibration or 0 for Normal Mode:");
  while (!Serial.available());
  char userChoice = Serial.read();

  if (userChoice == '1') {
    Serial.println("Entering Calibration Mode...");
    performCalibration();
  } else if (!loadCalibration()) {
    Serial.println("No Calibration Data Found! Starting Calibration...");
    performCalibration();
  } else {
    Serial.println("Calibration Data Loaded Successfully.");
  }

  // Generate log file name
  logFileName = getNextLogFileName();
  Serial.print("Log File: ");
  Serial.println(logFileName);

  Serial.println("Initialization Complete. Starting Program...");
  lcd.setCursor(0, 1);
  lcd.print("Scale Ready!");
  delay(2000);
  lcd.clear();

  // Setup buttons
  pinMode(zeroLeftButton, INPUT);
  pinMode(logRightButton, INPUT);

  // Start timing
  startTime = millis();
}

void loop() {
  // Update load cell state dynamically
  updateLoadCellState();

  // Read weights
  float weight1 = getWeight1();
  float weight2 = getWeight2();
  float weight3 = isThirdLoadCellConnected() ? getWeight3() : NAN;

  // Display weights on LCD
  displayWeights(lcd, weight1, weight2, weight3, logging);

  // Handle zero button
  if (digitalRead(zeroLeftButton) == HIGH) {
    tareAllLoadCells();
    Serial.println("Scales Zeroed!");
  }

  // Handle log button
  if (digitalRead(logRightButton) == HIGH) {
    logging = !logging;
    Serial.print("Logging: ");
    Serial.println(logging ? "ON" : "OFF");
  }

  // Log data if logging is enabled
  if (logging) {
    logData(logFileName, weight1, weight2, isThirdLoadCellConnected() ? weight3 : NAN, startTime, lcd);
  }

  delay(500);
}
