#line 2 "DigitalOutputTest.ino"

#include <AUnit.h>
#include "PinMock.h"
#include "DigitalOutput.h"

#define D8 15

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
  PinMock *pin = new PinMock(D8);
  DigitalOutput *output = new DigitalOutput(pin);

  void setup() override {
    TestOnce::setup();
    pin->setValue(LOW);
  }

  void assertIsOffAtBootPinLow() {
    assertFalse(output->isActive());
  }

  void assertToggleSwitchState() {
    bool state = output->isActive();
    output->toggle();
    assertNotEqual(state, output->isActive());
    state = output->isActive();
    output->toggle();
    assertNotEqual(state, output->isActive());
  }

  void assertOffTurnsOffOnlyIfOn() {
    assertFalse(output->isActive());
    output->off();
    assertFalse(output->isActive());
    output->on();
    assertTrue(output->isActive());
    output->off();
    assertFalse(output->isActive());
  }

  void assertOnTurnsOnOnlyIfOff() {
    assertFalse(output->isActive());
    output->on();
    assertTrue(output->isActive());
    output->on();
    assertTrue(output->isActive());
  }
};

testF(CustomTestOnce, assertIsOffAtBootPinLow) {
  assertIsOffAtBootPinLow();
}

testF(CustomTestOnce, assertToggleSwitchState) {
  assertToggleSwitchState();
}

testF(CustomTestOnce, assertOffTurnsOffOnlyIfOn) {
  assertOffTurnsOffOnlyIfOn();
}

testF(CustomTestOnce, assertOnTurnsOnOnlyIfOff) {
  assertOnTurnsOnOnlyIfOff();
}
