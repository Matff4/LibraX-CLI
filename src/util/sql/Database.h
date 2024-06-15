//
// Created by Matff on 08/05/2024.
//

#ifndef LIBRAX_DATABASE_H
#define LIBRAX_DATABASE_H

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>

#include <vector>
#include <print>
#include "../../model/Book.h"

class Database {
private:
    // Database configuration
    const std::string HOST = "tcp://127.0.0.1:3306";
    const std::string USER = "librax_usr";
    const std::string PASS = "librapasswd";
    const std::string DATABASE = "librax_db";

    std::unique_ptr<sql::Connection> connection;

public:
    Database();
    ~Database();

    std::vector<Book*> getBooks() const;
    void addBook(const Book &book) const;
    void removeBook(int idx) const;
};


#endif //LIBRAX_DATABASE_H
