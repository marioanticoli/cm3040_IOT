#include "ControlPlantCare.h"
#include "IRWrapper.h"

#define PLANT_SIZE 3

ControlPlantCare::ControlPlantCare(DigitalOutput* led, NCRelayController* pump)
  : led(led), pump(pump) {
  setting = std::vector<PlantSetting>(PLANT_SIZE);
  auto v = std::vector<Action>{ Action::TOGGLE_LED, Action::TOGGLE_PUMP, Action::SET_PLANT };
  // main = new Menu<Action>(v);
  v = std::vector<Action>{ Action::SET_HUMIDITY, Action::SET_LUMINOSITY, Action::BACK };
  // sub = new Menu<Action>(v);
  currMenu = main;
}

bool ControlPlantCare::isActive() {
  return active;
}

void ControlPlantCare::toggle() {
  active != active;
  currMenu = main;
}

void ControlPlantCare::action(uint32_t command) {
  setMenuDisplay();

  // switch (command) {
  //   case IRWrapper::key::FAST_FORWARD:
  //     currMenu->next();
  //     break;
  //   case IRWrapper::key::PAUSE:
  //     execHandler(currMenu->getItem());
  //     break;
  //   case IRWrapper::key::NR_1:
  //     if (currMenu == sub) currPlantSetting = 0;
  //     break;
  //   case IRWrapper::key::NR_2:
  //     if (currMenu == sub) currPlantSetting = 1;
  //     break;
  //   case IRWrapper::key::NR_3:
  //     if (currMenu == sub) currPlantSetting = 2;
  //     break;
  //   case IRWrapper::key::DOWN:
  //     if (currMenu == sub && currPlantSetting) adjustValue(-5);
  //     break;
  //   case IRWrapper::key::UP:
  //     if (currMenu == sub && currPlantSetting) adjustValue(5);
  //     break;
  // }
}

void ControlPlantCare::setMenuDisplay() {
  // switch (currMenu->getItem()) {
  //   case Action::TOGGLE_LED:
  //     line[0] = String("Toggle LED");
  //     line[1] = String("Switch " + led->isActive() ? "OFF" : "ON");
  //     break;
  //   case Action::TOGGLE_PUMP:
  //     line[0] = String("Toggle pump");
  //     line[1] = String("Switch " + pump->isActive() ? "OFF" : "ON");
  //     break;
  //   case Action::SET_PLANT:
  //     line[0] = String("Set plant");
  //     line[1] = String("Press 'PLAY' then number [1-3]");
  //     break;
  //   case Action::SET_HUMIDITY:
  //     line[0] = String("Humidity plant ") + String(currPlantSetting + 1);
  //     line[1] = String(setting[currPlantSetting].getHumidity()) + String("%");
  //     break;
  //   case Action::SET_LUMINOSITY:
  //     line[0] = String("Light plant ") + String(currPlantSetting + 1);
  //     line[1] = String(setting[currPlantSetting].getLuminosity()) + String("%");
  //     break;
  //   case Action::BACK:
  //     line[0] = String("Back to main menu");
  //     line[1] = String("");
  //     break;
  // }
}

void ControlPlantCare::execHandler(Action action) {
  switch (action) {
    case Action::TOGGLE_LED:
      led->toggle();
      break;
    case Action::TOGGLE_PUMP:
      pump->toggle();
      break;
    case Action::SET_PLANT:
      currMenu = sub;
      break;
    case Action::BACK:
      currMenu = main;
      break;
  }
}

void ControlPlantCare::adjustValue(int8_t value) {
  // PlantSetting plant = setting[currPlantSetting];
  // if (currMenu->getItem() == Action::SET_LUMINOSITY) {
  //   plant.incLuminosity(value);
  // } else if (currMenu->getItem() == Action::SET_HUMIDITY) {
  //   plant.incHumidity(value);
  // }
}

String* ControlPlantCare::getLines() {
  return line;
}
