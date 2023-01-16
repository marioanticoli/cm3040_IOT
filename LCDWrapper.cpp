#include "Arduino.h"
#include "LCDWrapper.h"

LCDWrapper::LCDWrapper(uint8_t address, uint8_t cols, uint8_t rows, bool allowScroll)
  : lcd(LiquidCrystal_I2C(address, cols, rows)), cols(cols), rows(rows) {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  if(allowScroll) {
    lcd.autoscroll();
  }
}

bool LCDWrapper::display(uint8_t line, uint8_t column, String msg) {
  Serial.println(msg);
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