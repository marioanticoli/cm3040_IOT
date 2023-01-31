#pragma once
#ifndef Menu_h
#define Menu_h
#include <vector>
#include "Arduino.h"

// Menu class

template <class T>
class Menu {
private:
  std::vector<T> menu;
  uint8_t current;

public:
  // Initialise the menu
  Menu(std::vector<T>);
  // Returns the current item in the menu
  T getItem();
  // Move to the next item in menu
  void next();
};

#endif
