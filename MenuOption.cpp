#include "MenuOption.h"

MenuOption::MenuOption(std::string _text, void (*_action)(), bool _available)
    : text(_text), action(_action), available(_available) {}
