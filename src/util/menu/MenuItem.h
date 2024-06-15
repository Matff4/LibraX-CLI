//
// Created by Matff on 08/05/2024.
//

#ifndef LIBRAX_MENUITEM_H
#define LIBRAX_MENUITEM_H

#include <print>
#include <vector>
#include <string>
#include <iostream>
#include "MenuOption.h"


class MenuItem {
private:
    std::string name;
    std::vector<MenuItem*> subItems;
    std::vector<MenuOption*> options;
    bool isMain;

public:
    explicit MenuItem(std::string  name, bool isMain = false);

    std::string getName();

    void addSubItem(MenuItem* item);

    void addOption(MenuOption* option);

    void display();

    ~MenuItem();
};

#endif //LIBRAX_MENUITEM_H
