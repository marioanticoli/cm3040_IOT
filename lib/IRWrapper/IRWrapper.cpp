#include "IRWrapper.h"

IRWrapper::IRWrapper(uint8_t pin, uint16_t debounce)
  : receiver(IRrecv(pin)), debounce(debounce) {
  pinMode(pin, INPUT);
  // Start the receiver
  receiver.enableIRIn();
  Serial.println(F("Ready to receive IR signals"));
}

uint32_t IRWrapper::getInput() {
  decode_results results;
  // Check if signal received
  if (receiver.decode(&results)) {
    // debounce
    delay(debounce);
    // listen for next value
    receiver.resume();
    return results.value;
  }
  return 0;
}
