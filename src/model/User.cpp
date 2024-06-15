//
// Created by Matff on 15/06/2024.
//

#include "User.h"

int User::getId() const {
    return id;
}

const std::string &User::getFirstname() const {
    return firstname;
}

const std::string &User::getLastname() const {
    return lastname;
}

const std::string &User::getRentedBookIds() const {
    return rented_books_id;
}

void User::print() const {
    std::println("|{:^6}|{:^20}|{:^20}|{:^50}|",
                 this->getId(), this->getFirstname(),
                 this->getLastname(), this->getRentedBookIds()
    );
}
