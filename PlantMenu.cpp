#include "PlantMenu.h"
#include "IRWrapper.h"


PlantMenu::PlantMenu(std::vector<PlantSetting> setting)
  : settings(setting) {
  menu = new Menu(std::vector{ Action::TOGGLE_LED, Action::TOGGLE_PUMP, Action::SET_PLANT });
  submenu = new Menu(std::vector{ Action::SET_HUMIDITY, Action::SET_LUMINOSITY });
}

bool PlantMenu::isActive() {
  return isActive;
}

void PlantMenu::toggle() {
  isActive != isActive;
  currMenu = main;
}

void PlantMenu::action(uint32_t command) {
  switch (command) {
    case IRWrapper::key::FAST_FORWARD:
      currMenu->next();
      break;
    case IRWrapper::key::PAUSE:
      execHandler((Action)currMenu->getItem());
      break;
    case IRWrapper::key::NR_1:
      if(currMenu == sub) currPlantSetting = 0;
      break;
    case IRWrapper::key::NR_2:
      if(currMenu == sub) currPlantSetting = 1;
      break;
    case IRWrapper::key::NR_3:
      if(currMenu == sub) currPlantSetting = 2;
      break;
  }
}

void PlantMenu::execHandler(Action action) {
  switch(action) {
    case Action::TOGGLE_LED:
      
  }
}

String PlantMenu::line1() {
  return line1;
}

String PlantMenu::line2() {
  return line2;
}

















// // constructor

//   showMenu = false;
//   mainMenu = true;
//   currMenu = menu;
//   currPlantSetting = 0;
//   inputMode = false;







// //loop
//     showMenu = !showMenu;
//     mainMenu = true;

//     currMenu = mainMenu ? menu : plantMenu;




// void menuAction() {

// }

// void menuHandler(Action action) {
//   switch (action) {
//     case Action::SET_HUMIDITY:
//       inputMode = true;
//       inputType = Type::HUMIDITY;
//       inputValue = settings[currPlantSetting].getHumidity();
//       break;
//     case Action::SET_LUMINOSITY:
//       inputMode = true;
//       inputType = Type::LUMINOSITY;
//       inputValue = settings[currPlantSetting].getLuminosity();
//       break;
//   }
// }

// void showMenuText() {
//   String line1, line2;
//   switch (currMenu->getItem()) {
//     case Action::TOGGLE_LED:
//       line1 = "Toggle LED";
//       line2 = "Switch " + led->isActive() ? "OFF" : "ON";
//       break;
//     case Action::TOGGLE_PUMP:
//       line1 = "Toggle Pump";
//       line2 = "Switch " + pump->isActive() ? "OFF" : "ON";
//       break;
//     case Action::SET_PLANT:
//       line1 = "Plant settings";
//       line2 = "";
//       break;
//     case Action::SET_HUMIDITY:
//       line1 = "Plant " + (currPlantSetting + 1) + ": Hum.";
//       line2 = settings[currPlantSetting].getHumidity() + "%";
//       break;
//     case Action::SET_LUMINOSITY:
//       line1 = "Plant " + (currPlantSetting + 1) + ": Light";
//       line2 = settings[currPlantSetting].getLuminosity() + "%";
//   }
//   lcd->display(0, 0, line1);
//   lcd->display(1, 0, line2);
// }
