#ifndef MENUOPTION_H
#define MENUOPTION_H

#include <string>

class MenuOption {
public:
    std::string text;
    void (*action)();
    bool available;

    MenuOption(std::string _text, void (*_action)(), bool _available = true);
};

#endif 
