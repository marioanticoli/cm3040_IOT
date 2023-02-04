#pragma once
#ifndef Menu_h
#define Menu_h

// Menu class

template <typename T>
class Menu {
private:
  T* menu;
  uint8_t size;
  uint8_t current;

public:
  // Initialise the Menu
  // implementation in the header file to make it visible to calling classes
  Menu(T menu[], uint8_t size) : 
    size(size), current(0) {
    this->menu = new T[size];
    for (uint8_t i = 0; i < size; i++) this->menu[i] = menu[i];
  }

  // Returns the current item in the menu
  T getItem() {
    return menu[current];
  }

  // Move to the next item in menu
  void next() {
    current = (current + 1) % size;
  }

  void reset() {
    current = 0;
  }
};

#endif
