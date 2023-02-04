#include "Arduino.h"
#include "LCDWrapper.h"

const String EMPTY_LINE = "                "; // 16 character long, to clear a line

LCDWrapper::LCDWrapper(uint8_t address, uint8_t cols, uint8_t rows)
  : lcd(LiquidCrystal_I2C(address, cols, rows)), cols(cols), rows(rows) {
  on = false;
  toggle();
}

bool LCDWrapper::display(uint8_t line, uint8_t column, String msg) {
  // Display if position within the limits of the LCD
  if (line < rows && column < cols) {
    if(!msg.equals(lastMsg[line])) {
      lcd.setCursor(0, line);
      lcd.print(EMPTY_LINE);
      lastMsg[line] = msg;
    }
    lcd.setCursor(column, line);
    lcd.print(msg);
    return true;
  } else {
    return false;
  }
}

void LCDWrapper::clear() {
  lastMsg[0] = EMPTY_LINE;
  lastMsg[1] = EMPTY_LINE;
  lcd.clear();
}

void LCDWrapper::clear(uint8_t line) {
  if(line <= rows - 1) {
    lastMsg[line] = EMPTY_LINE;
    display(line, 0, EMPTY_LINE);
  }
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
