//
// Created by Matff on 08/05/2024.
//

#include "Book.h"

int Book::getId() const {
    return id;
}

const std::string &Book::getIsbn() const {
    return isbn;
}

const std::string &Book::getTitle() const {
    return title;
}

const std::string &Book::getAuthor() const {
    return author;
}

int Book::getYear() const {
    return year;
}

int Book::getQty() const {
    return qty;
}

int Book::getRented() const {
    return rented;
}

void Book::print() const {
    std::println("|{:^6}|{:^20}|{:^40}|{:^30}|{:^6}|{:^5}|{:^8}|",
                 this->getId(), this->getIsbn(), this->getTitle(),
                 this->getAuthor(), this->getYear(), this->getQty(),
                 this->getRented()
    );
}
