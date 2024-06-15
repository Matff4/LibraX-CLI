//
// Created by Matff on 08/05/2024.
//

#include "MenuItem.h"
#include "../screen/Screen.h"

MenuItem::MenuItem(std::string name, bool isMain) : name(std::move(name)), isMain(isMain) {}

std::string MenuItem::getName() {
    return this->name;
}


void MenuItem::addSubItem(MenuItem* item) {
    subItems.push_back(item);
}

void MenuItem::addOption(MenuOption *option) {
    options.push_back(option);
}


void MenuItem::display() {
    while(true) {
        Screen::clear();

        int idx = 1;

        std::println("-------- {} --------", name);

        // Print submenus
        for (const auto& item : subItems) {
            std::println("{}. {}", idx++, item->getName());
        }

        for(const auto& option : options) {
            std::println("{}. {}", idx++, option->getName());
        }

        // Print exit or back
        std::println("0. {}", (isMain ? "Exit" : "Back"));
        std::print("Enter your choice: ");

        char ch_input;
        std::cin.clear();
        std::cin.get(ch_input);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        int input = ch_input - '0';

        if(input == 0) {
            break;
        } else if(!subItems.empty() && input >= 1 && input <= subItems.size()) {
            subItems[input - 1]->display();
        } else if(!options.empty() && input >= 1 && input <= (options.size() + subItems.size())) {
            options[input - 1 - subItems.size()]->execute();
        } else {
            std::println("Invalid choice. Please try again.");
            std::cin.get();
            std::cin.clear();
        }
    }
}

MenuItem::~MenuItem() {
    for (auto& item : subItems) {
        delete item;
    }
    subItems.clear();
}