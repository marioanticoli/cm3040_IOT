#include "IRWrapper.h"

IRWrapper::IRWrapper(uint8_t pin)
  : receiver(IRrecv(pin)) {
  // Start the receiver
  receiver.enableIRIn();
  Serial.print(F("Ready to receive IR signals"));
}

uint32_t IRWrapper::getInput() {
  decode_results results;
  // Check if signal received
  if (receiver.decode(&results)) {
    // debounce
    delay(200);
    // listen for next value
    receiver.resume();
    return results.value;
  }
  return 0;
}
