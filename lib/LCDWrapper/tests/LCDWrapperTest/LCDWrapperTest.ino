#line 2 "LCDWrapperTest.ino"

#include <AUnit.h>
#include "LCDWrapper.h"

using namespace aunit;

// in setup, we prepare the serial port.
void setup() {
  Serial.setDebugOutput(true);
  Serial.begin(9600);
  while (!Serial)
    ;
}

// we just call the test runner in loop
void loop() {
  TestRunner::run();
}

class CustomTestOnce : public TestOnce {
protected:
  LCDWrapper *lcd = new LCDWrapper(0x27, 5, 2); // LCD with 5 cols, 2 rows

  void assertToggleDisplay() {
    assertTrue(lcd->isOn());
    lcd->toggle();
    assertFalse(lcd->isOn());
  }

  void assertDisplayOnlyIfCoordWithinBoundaries() {
    assertFalse(lcd->display(10, 10, "Test"));
    assertTrue(lcd->display(0, 0, "Test"));
  }
};

testF(CustomTestOnce, assertToggleDisplay) {
  assertToggleDisplay();
}

testF(CustomTestOnce, assertDisplayOnlyIfCoordWithinBoundaries) {
  assertDisplayOnlyIfCoordWithinBoundaries();
}

