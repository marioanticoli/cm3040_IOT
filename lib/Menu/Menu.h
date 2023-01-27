#pragma once
#ifndef Menu_h
#define Menu_h
#include "IRWrapper.h"

// Menu class
enum class Action {
  NEXT,
  TOGGLE_LCD,
  TOGGLE_PUMP,
  TOGGLE_LED,
  SET_PLANT_PARAMS,
  NOOP,
};

class Menu {
private:
  struct Node {
    Action selected;
    struct Node* next;
  };

  Node item1, item2, item3;

  struct Node* current;

public:
  // Initialise the menu
  Menu();
  // Returns text of the current line in the menu
  String display();
  // Returns an action based on the command received
  Action getAction(IRWrapper::key, bool);
  // Move to next item in menu and returns text to display
  String getNext();

};

#endif
