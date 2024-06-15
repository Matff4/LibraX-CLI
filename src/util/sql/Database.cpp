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

void Database::addUser(const User &user) const {
    const std::string query = std::format(
        "INSERT INTO users (firstname, lastname, rented_books) VALUES ('{}', '{}', '');",
        user.getFirstname(), user.getLastname()
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

void Database::removeUser(int idx) const {
    const std::string query = std::format("DELETE FROM users WHERE id={};", idx);

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

void Database::rentBook(int idUsr, int idBook) const {
    const std::string query_select = std::format("SELECT rented_books FROM users WHERE id = {};", std::to_string(idUsr));

    try {
        const std::unique_ptr<sql::Statement> stmt_select(this->connection->createStatement());
        const std::unique_ptr<sql::ResultSet> res_select(stmt_select->executeQuery(query_select));

        std::string rentedBooks;

        if (res_select->next()) {
            rentedBooks = res_select->getString("rented_books");
            if (!rentedBooks.empty()) {
                rentedBooks += ", ";
            }
            rentedBooks += std::to_string(idBook);
        }

        const std::string query_update = std::format("UPDATE users SET rented_books = '{}' WHERE id = '{}';", rentedBooks, std::to_string(idUsr));

        const std::unique_ptr<sql::Statement> stmt_update(this->connection->createStatement());
        const std::unique_ptr<sql::ResultSet> res_update(stmt_select->executeQuery(query_update));

    } catch (sql::SQLException &e) {
        if(e.getErrorCode() != 0) {
            std::cerr << "SQLException: " << e.what() << std::endl;
            std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
            std::cerr << "SQLState: " << e.getSQLState() << std::endl;
        }
    }
}

void Database::returnBook(int idUsr, int idBook) const {
    const std::string query_select = std::format("SELECT rented_books FROM users WHERE id = {};", std::to_string(idUsr));

    try {
        const std::unique_ptr<sql::Statement> stmt_select(this->connection->createStatement());
        const std::unique_ptr<sql::ResultSet> res_select(stmt_select->executeQuery(query_select));

        std::string rentedBooks;

        if(!rentedBooks.contains(std::to_string(idBook)) )

        if (res_select->next()) {
            rentedBooks = res_select->getString("rented_books");
            if (!rentedBooks.empty()) {
                rentedBooks += ", ";
            }
            rentedBooks += std::to_string(idBook);
        }

        const std::string query_update = std::format("UPDATE users SET rented_books = '{}' WHERE id = '{}';", rentedBooks, std::to_string(idUsr));

        const std::unique_ptr<sql::Statement> stmt_update(this->connection->createStatement());
        const std::unique_ptr<sql::ResultSet> res_update(stmt_select->executeQuery(query_update));

    } catch (sql::SQLException &e) {
        if(e.getErrorCode() != 0) {
            std::cerr << "SQLException: " << e.what() << std::endl;
            std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
            std::cerr << "SQLState: " << e.getSQLState() << std::endl;
        }
    }
}