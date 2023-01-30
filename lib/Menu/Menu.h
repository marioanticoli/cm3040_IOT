#pragma once
#ifndef Menu_h
#define Menu_h
#include "IRWrapper.h"
#include <vector>

// Menu class

template <class T>
class Menu {
private:
  std::vector<T> menu;
  uint8_t current;

public:
  // Initialise the menu
  Menu(std::vector<T>);
  // Returns the value of current item in the menu
  int getItem();
  // Move to next item in menu
  void next();
};

#endif
