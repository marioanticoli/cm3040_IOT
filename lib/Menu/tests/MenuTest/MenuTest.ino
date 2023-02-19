#line 2 "MenuTest.ino"

#include <AUnit.h>
#include "Menu.h"

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
  String arr[3] = { "Item1", "Item2", "Item3" };
  Menu<String> *menu;

  void setup() override {
    TestOnce::setup();
    menu = new Menu<String>(arr, 3);
  }

  // optional
  void teardown() override {
    TestOnce::teardown();
  }

  void assertMenuStartsAtFirstItem() {
    String expected = arr[0];
    String actual = menu->getItem();
    assertTrue(expected.equals(actual));
  }

  void assertMenuGoNext() {
    String expected = arr[1];
    menu->next();
    String actual = menu->getItem();
    assertTrue(expected.equals(actual));
  }

  void assertMenuRewinds() {
    String expected = arr[0];
    menu->next();
    menu->next();
    menu->next();
    String actual = menu->getItem();
    assertTrue(expected.equals(actual));
  }

  void assertMenuResets() {
    String expected = arr[0];
    menu->next();
    menu->reset();
    String actual = menu->getItem();
    assertTrue(expected.equals(actual));
  }
};

testF(CustomTestOnce, assertMenuStartsAtFirstItem) {
  assertMenuStartsAtFirstItem();
}

testF(CustomTestOnce, assertMenuGoNext) {
  assertMenuGoNext();
}

testF(CustomTestOnce, assertMenuRewinds) {
  assertMenuRewinds();
}

testF(CustomTestOnce, assertMenuResets) {
  assertMenuResets();
}
