#include "Arduino.h"
#include "LCDWrapper.h"

LCDWrapper::LCDWrapper(uint8_t address, uint8_t cols, uint8_t rows)
  : lcd(LiquidCrystal_I2C(address, cols, rows)), cols(cols), rows(rows) {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

bool LCDWrapper::display(uint8_t line, uint8_t column, String msg, bool allowScroll) {
  Serial.println(msg);
  if (line < rows && column < cols) {
    lcd.setCursor(column, line);
    if (allowScroll || (msg.length() > cols)) {
      lcd.autoscroll();
    } else {
      lcd.noAutoscroll();
    }
    lcd.print(msg);
    return true;
  } else {
    return false;
  }
}

void LCDWrapper::clear() {
  lcd.clear();
}