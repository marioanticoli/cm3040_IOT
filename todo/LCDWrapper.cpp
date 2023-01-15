#include "Arduino.h"
#include "LCDWrapper.h"

LCDWrapper::LCDWrapper(uint8_t address, uint8_t cols, uint8_t rows) : lcd(address, cols, rows), cols(cols), rows(rows) {
  lcd.init();
  lcd.backlight();
}

bool LCDWrapper::display(uint8_t line, uint8_t column, String msg) {
  if(line < rows && column < cols) {
    lcd.setCursor(line, column);
    lcd.print(msg);
    return true;  
  } else {
    return false;
  }
}
