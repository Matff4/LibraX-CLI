//
// Created by Matff on 15/06/2024.
//

#ifndef LIBRAX_USER_H
#define LIBRAX_USER_H

#include <string>
#include <print>
#include <utility>

class User {
private:
    int id;
    std::string firstname;
    std::string lastname;
    std::string rented_books_id;

public:
    User(const int id, std::string firstname, std::string lastname, std::string rented_books_id):
          id(id),
          firstname(std::move(firstname)),
          lastname(std::move(lastname)),
          rented_books_id(std::move(rented_books_id)) {
    }

    int getId() const;

    const std::string &getFirstname() const;

    const std::string &getLastname() const;

    const std::string &getRentedBookIds() const;

    void print() const;
};


#endif //LIBRAX_USER_H
