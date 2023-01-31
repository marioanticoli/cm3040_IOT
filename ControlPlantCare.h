#pragma once
#ifndef ControlPlantCare_h
#define ControlPlantCare_h
#include <vector>
#include "PlantSetting.h"
#include "Menu.h"
#include "DigitalOutput.h"
#include "NCRelayController.h"

// ControlPlantCare class

enum class Action {
  TOGGLE_LED,
  TOGGLE_PUMP,
  SET_PLANT,
  SET_HUMIDITY,
  SET_LUMINOSITY,
  BACK,
};

class ControlPlantCare {
private:
  std::vector<PlantSetting> setting;
  Menu<Action> *main;
  Menu<Action> *sub;
  Menu<Action> *currMenu;
  DigitalOutput *led;
  NCRelayController *pump;
  bool active;
  String *line = new String[2];
  uint currPlantSetting;

  void setMenuDisplay();
  void execHandler(Action);
  void adjustValue(int8_t);


public:
  // Initialise the ControlPlantCare
  ControlPlantCare(DigitalOutput *, NCRelayController *);
  bool isActive();
  void toggle();
  void action(uint32_t);
  String *getLines();
};

#endif
