#include "Menu.h"
#include "Arduino.h"

Menu::Menu() {
  item1.selected = Action::TOGGLE_LED;
  item1.next = &item2;

  item2.selected = Action::TOGGLE_PUMP;
  item2.next = &item3;

  item3.selected = Action::SET_PLANT_PARAMS;
  item3.next = &item1;

  current = &item1;
}

Action Menu::getAction(IRWrapper::key key, bool mode) {
  switch (key) {
    case IRWrapper::key::FAST_FORWARD:
      return Action::NEXT;
    case IRWrapper::key::PAUSE:
      return current->selected;
    default:
      return Action::NOOP;
  }
}

String Menu::display() {
  switch(current->selected) {
    case Action::TOGGLE_LCD:
      return String("Toggle LCD");
    case Action::TOGGLE_PUMP:
      return String("Toggle water pump");
    case Action::TOGGLE_LED:
      return String("Toggle LED");
    case Action::SET_PLANT_PARAMS:
      return String("Plant settings");
    default:
      return "Error!";
  }
}

String Menu::getNext() {
  current = current->next;
  return display();
}

