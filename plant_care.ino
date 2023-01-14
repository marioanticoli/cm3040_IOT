#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2)

void setup() {
  lcd.init();
  lcd.backlight();
}

void loop() {
  displayData("prova", 0, 0);
}

void displayData(String msg, int line, int column) {
  lcd.setCursor(line, column);
  lcd.print(msg);
}
