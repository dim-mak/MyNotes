#include <Wire.h>
#include <LiquidCrystal.h>

// Chip Select for microSD card
const int CHIP_SELECT_PIN = 53;

// LCD setup
const int rs = A3, en = A5, d4 = A9, d5 = A10, d6 = A11, d7 = A12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Buttons
const int zeroLeftButton = 2;
const int logRightButton = 3;

// Loadcell Pins
const int DT1 = 6, SCK1 = 9;
const int DT2 = 7, SCK2 = 10;
const int DT3 = 8, SCK3 = 11;

// Loadcells
HX711 scale1, scale2, scale3;

// Variables
bool logging = false;
bool thirdLoadCellConnected = false;
unsigned long startTime = 0;
String logFileName;

void setup() {

    // LCD pins
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

    // Initialize loadcells    
    scale1.begin(DT1, SCK1);
    scale2.begin(DT2, SCK2);
    scale3.begin(DT3, SCK3);

    // Initialize SD card
    if (!SD.begin(CHIP_SELECT_PIN)) {
        centerMessage(lcd, "SD Card Error!");
        Serial.println("SD Card Error!");
    }

    thirdLoadCellConnected = scale3.is_ready();


}