//
// Created by Matff on 08/05/2024.
//

#ifndef LIBRAX_BOOK_H
#define LIBRAX_BOOK_H

#include <string>
#include <print>
#include <utility>

class Book {
private:
    int id;
    std::string isbn;
    std::string title;
    std::string author;
    int year;
    int qty;
    int rented;

public:
    Book(const int id, std::string isbn, std::string title, std::string author, const int year, const int qty, const int rented):
          id(id),
          isbn(std::move(isbn)),
          title(std::move(title)),
          author(std::move(author)),
          year(year),
          qty(qty),
          rented(rented) {
    }

    int getId() const;

    const std::string &getIsbn() const;

    const std::string &getTitle() const;

    const std::string &getAuthor() const;

    int getYear() const;

    int getQty() const;

    int getRented() const;

    void print() const;
};


#endif //LIBRAX_BOOK_H
