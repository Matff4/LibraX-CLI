//
// Created by Matff on 08/05/2024.
//

#include "Database.h"

Database::Database() {
    sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();

    // Establish a connection
    connection = std::unique_ptr<sql::Connection>(driver->connect(this->HOST, this->USER, this->PASS));
    connection->setSchema(this->DATABASE);

}

Database::~Database() {
    this->connection->close();
}

std::vector<std::unique_ptr<Book>> Database::getBooks() const {
    const std::unique_ptr<sql::Statement> stmt(this->connection->createStatement());
    const std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM books"));

    std::vector<std::unique_ptr<Book>> books;

    while (res->next()) {
        const int id               = res->getInt("id");
        const std::string isbn    = res->getString("isbn");
        const std::string title   = res->getString("title");
        const std::string author  = res->getString("author");
        const int year             = res->getInt("year");
        const int qty              = res->getInt("qty");
        const int rented           = res->getInt("rented");

        books.push_back(std::make_unique<Book>(id, isbn, title, author, year, qty, rented));
    }

    return books;
}

void Database::addBook(const Book &book) const {
    const std::string query = std::format(
        "INSERT INTO books (isbn, title, author, year, qty, rented) VALUES ('{}', '{}', '{}', {}, {}, {});",
        book.getIsbn(), book.getTitle(), book.getAuthor(), book.getYear(), book.getQty(), book.getRented()
    );

    try {
        const std::unique_ptr<sql::Statement> stmt(this->connection->createStatement());
        const std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));
    } catch (sql::SQLException &e) {
        if(e.getErrorCode() != 0) {
            std::cerr << "SQLException: " << e.what() << std::endl;
            std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
            std::cerr << "SQLState: " << e.getSQLState() << std::endl;
        }
    }

}

void Database::removeBook(int idx) const {
    const std::string query = std::format("DELETE FROM books WHERE id={};", idx);

    try {
        const std::unique_ptr<sql::Statement> stmt(this->connection->createStatement());
        const std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));
    } catch (sql::SQLException &e) {
        if(e.getErrorCode() != 0) {
            std::cerr << "SQLException: " << e.what() << std::endl;
            std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
            std::cerr << "SQLState: " << e.getSQLState() << std::endl;
        }
    }
}

std::vector<std::unique_ptr<User>> Database::getUsers() const {
    const std::unique_ptr<sql::Statement> stmt(this->connection->createStatement());
    const std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM users"));

    std::vector<std::unique_ptr<User>> users;

    while (res->next()) {
        const int id               = res->getInt("id");
        const std::string firstname    = res->getString("firstname");
        const std::string lastname    = res->getString("lastname");
        const std::string rented_books= res->getString("rented_books");


        users.push_back(std::make_unique<User>(id, firstname, lastname, rented_books));
    }

    return users;
}