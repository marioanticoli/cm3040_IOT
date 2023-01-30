#include "Menu.h"

Menu::Menu(std::vector<T> menu) : 
  menu(menu), current(0) {}

int Menu::getItem() {
  return menu[current];
}

void Menu::next() {
  current = (i + 1) % menu.size();
}

