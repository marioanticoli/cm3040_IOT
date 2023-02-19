#line 2 "NCRelayControllerTest.ino"

#include <AUnit.h>
#include "PinMock.h"
#include "NCRelayController.h"

#define D4 2  // D4 is HIGH at boot

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
  PinMock *pin = new PinMock(D4);
  NCRelayController *relay = new NCRelayController(pin);

  void setup() override {
    TestOnce::setup();
    pin->setValue(HIGH);
  }

  // optional
  void teardown() override {
    TestOnce::teardown();
  }

  void assertIsOffAtBootPinHigh() {
    assertFalse(relay->isActive());
  }

  void assertToggleSwitchState() {
    bool state = relay->isActive();
    relay->toggle();
    assertNotEqual(state, relay->isActive());
    state = relay->isActive();
    relay->toggle();
    assertNotEqual(state, relay->isActive());
  }

  void assertOffTurnsOffOnlyIfOn() {
    assertFalse(relay->isActive());
    relay->off();
    assertFalse(relay->isActive());
    relay->on();
    assertTrue(relay->isActive());
    relay->off();
    assertFalse(relay->isActive());
  }

  void assertOnTurnsOnOnlyIfOff() {
    assertFalse(relay->isActive());
    relay->on();
    assertTrue(relay->isActive());
    relay->on();
    assertTrue(relay->isActive());
  }
};

testF(CustomTestOnce, assertIsOffAtBootPinHigh) {
  assertIsOffAtBootPinHigh();
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