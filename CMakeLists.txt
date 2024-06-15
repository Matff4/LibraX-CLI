cmake_minimum_required(VERSION 3.28)
project(LibraX)

include_directories(. "/usr/include/cppconn")

set(CMAKE_CXX_STANDARD 26)

add_executable(LibraX src/main.cpp

        src/util/menu/MenuItem.cpp
        src/util/menu/MenuItem.h
        src/util/menu/MenuOption.cpp
        src/util/menu/MenuOption.h

        src/util/screen/Screen.cpp
        src/util/screen/Screen.h

        src/util/sql/Database.cpp
        src/util/sql/Database.h

        src/model/Book.cpp
        src/model/Book.h)


target_link_libraries(LibraX mysqlcppconn)