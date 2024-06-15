//
// Created by Matff on 08/05/2024.
//

#ifndef LIBRAX_MENUOPTION_H
#define LIBRAX_MENUOPTION_H

#include <print>
#include <functional>
#include <string>

class MenuOption {
private:
    std::string name;
    std::function<void()> callback;

public:
    MenuOption(std::string  name, const std::function<void()>& callback);

    std::string getName() const;

    void execute() const;
};

#endif //LIBRAX_MENUOPTION_H
