#ifndef Menu_h
#define Menu_h
#include "Arduino.h"
#include "IRWrapper.h"

// Menu class

class Menu {
private:
  struct Node {
    String text;
    struct Node* next;
  };

  struct Node* current;

public:
  // Initialise the menu
  Menu();
  // Returns text of the current line in the menu
  String display();
  // Returns an action based on the command received
  uint8_t getAction(IRWrapper::key);
  // Move to next item in menu and returns text to display
  String getNext();

  enum action {
    LCD_TOGGLE = 1,
    PUMP_TOGGLE = 2,
    LED_TOGGLE = 3,
    SET_PLANT_PARAMS = 4,
    NOOP = 0
  };
};

#endif
