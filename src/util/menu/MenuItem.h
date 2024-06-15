//
// Created by Matff on 08/05/2024.
//

#ifndef LIBRAX_MENUITEM_H
#define LIBRAX_MENUITEM_H

#include <print>
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "MenuOption.h"


class MenuItem {
private:
    std::string name;
    std::vector<std::unique_ptr<MenuItem>> subItems;
    std::vector<std::unique_ptr<MenuOption>> options;
    bool isMain;

public:
    explicit MenuItem(std::string  name, bool isMain = false);

    std::string getName();

    void addSubItem(std::unique_ptr<MenuItem> item);
    void addOption(std::unique_ptr<MenuOption> option);

    void display();

    //~MenuItem();
};

#endif //LIBRAX_MENUITEM_H
