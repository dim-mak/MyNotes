#include "utilities.h"


String adjustPrecision(float weight) {
  if (isnan(weight)) return "N/A";
  return String(weight, abs(weight) < 1.0 ? 3 : (abs(weight) < 10.0 ? 2 : 1));
}

void displayWeights(LiquidCrystal &lcd, float w1, float w2, float w3, bool logging) {
  lcd.setCursor(0, 0);
  lcd.print(adjustPrecision(w1) + "|" + adjustPrecision(w2) + "|");
  lcd.print(isnan(w3) ? "N/A" : adjustPrecision(w3));

  lcd.setCursor(5, 2);
  lcd.print("Log: ");
  lcd.print(logging ? "ON " : "OFF ");
}

void centerMessage(LiquidCrystal &lcd, const char *message) {
  lcd.clear();
  lcd.setCursor((20 - strlen(message)) / 2, 1);
  lcd.print(message);
}