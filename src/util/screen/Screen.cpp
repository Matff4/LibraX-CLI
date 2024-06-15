//
// Created by Matff on 08/05/2024.
//

#include "Screen.h"

void Screen::clear() {
    std::println("\x1B[2J\x1B[H");
}
