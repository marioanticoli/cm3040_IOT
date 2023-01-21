#include "Arduino.h"
#include "LCDWrapper.h"

LCDWrapper::LCDWrapper(uint8_t address, uint8_t cols, uint8_t rows)
  : lcd(LiquidCrystal_I2C(address, cols, rows)), cols(cols), rows(rows) {
  on = false;
  toggle();
}

bool LCDWrapper::display(uint8_t line, uint8_t column, String msg) {
  Serial.println(msg);
  // Display if position within the limits of the LCD
  if (line < rows && column < cols) {
    lcd.setCursor(column, line);
    lcd.print(msg);
    return true;
  } else {
    return false;
  }
}

void LCDWrapper::clear() {
  lcd.clear();
}

void LCDWrapper::toggle() {
  if (on) {
    lcd.noBacklight();
  } else {
    lcd.init();
    lcd.backlight();
    lcd.clear();
  }
  on = !on;
}
