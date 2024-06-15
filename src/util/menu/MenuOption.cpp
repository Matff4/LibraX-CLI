//
// Created by Matff on 08/05/2024.
//

#include "MenuOption.h"

MenuOption::MenuOption(std::string name, const std::function<void()>& callback) : name(std::move(name)), callback(callback) {}

std::string MenuOption::getName() const {
    return this->name;
}

void MenuOption::execute() const {
    if (callback) {
        callback();
    }
}
