#include "Menu.h"

Menu::Menu() {
  Node item1, item2, item3, item4;
  current = &item1;
  item1.text = "Toggle LCD";
  item1.next = &item2;
  item2.text = "Toggle water pump";
  item2.next = &item3;
  item3.text = "Toggle LED";
  item3.next = &item4;
  item4.text = "Plant settings";
  item4.next = &item1;
}

uint8_t Menu::getAction(IRWrapper::key key) {
  switch (key) {
    case IRWrapper::key::POWER:
      return LCD_TOGGLE;
    case IRWrapper::key::PAUSE:
      return LED_TOGGLE;
    case IRWrapper::key::EQ:
      return PUMP_TOGGLE;
    case IRWrapper::key::FUNC_STOP:
      return SET_PLANT_PARAMS;
    default:
      return NOOP;
  }
}

String Menu::display() {
  return current->text;
}

String Menu::getNext() {
  current = current->next;
  return display();
}
