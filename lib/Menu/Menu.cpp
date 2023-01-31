#include "Menu.h"

template <class T>
Menu<T>::Menu(std::vector<T> menu) : 
  menu(menu), current(0) {}

template <class T>
T Menu<T>::getItem() {
  return menu[current];
}

template <class T>
void Menu<T>::next() {
  current = (current + 1) % menu.size();
}

