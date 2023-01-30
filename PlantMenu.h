#pragma once
#ifndef PlantMenu_h
#define PlantMenu_h
#include <vector>
#include "PlantSetting.h"
#include "Menu.h"

// PlantMenu class

enum Action : char {
  TOGGLE_LED,
  TOGGLE_PUMP,
  SET_PLANT,
  SET_HUMIDITY,
  SET_LUMINOSITY,
};

enum class Type {
  HUMIDITY,
  LUMINOSITY,
};

class PlantMenu {
private:
  std::vector<PlantSetting> setting;
  Menu<Action>* main, sub, currMenu;
  bool isActive;
  String line1, line2;


  // // Switch if menu or sensor data;
  // bool showMenu;
  // bool mainMenu;
  // bool inputMode;
  // Type inputType;
  // uint8_t inputValue;


public:
  // Initialise the PlantMenu
  PlantMenu(std::vector<PlantSetting>);
  bool isActive();
  void toggle();
  void action(uint32_t);
  String line1();
  String line2();
};

#endif