#line 2 "NCRelayControllerTest.ino"

#include <AUnit.h>
#include "PinMock.h"
#include "AnalogReader.h"

#define A0 0

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
  PinMock *pin = new PinMock(A0);

  void assertGetPercValue() {
    AnalogReader areader(pin, 1, 200);
    pin->setValue(100);
    long expected = 50;

    long actual = areader.get_perc_value();

    assertEqual(expected, actual);
  }

  void assertGetPercValueWhenInverted() {
    AnalogReader areader(pin, 1, 200, true);
    pin->setValue(200);
    long expected = 0;

    long actual = areader.get_perc_value();

    assertEqual(expected, actual);
  }
};

testF(CustomTestOnce, assertGetPercValue) {
  assertGetPercValue();
}

testF(CustomTestOnce, assertGetPercValueWhenInverted) {
  assertGetPercValueWhenInverted();
}
