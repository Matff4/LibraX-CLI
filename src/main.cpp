#include "util/menu/MenuItem.h"
#include "util/screen/Screen.h"
#include "util/sql/Database.h"
#include <memory>
#include <vector>
#include <format>
#include <iostream>

int main() {
    // Create database connection
    auto db = std::make_unique<Database>();

    /*
    *  ========== Create functions for MenuOption ==========
    */
    auto func_list_book = [&db]() {
        const std::vector<std::unique_ptr<Book>>& books = db->getBooks();
        std::string header = std::format("|{:^6}|{:^20}|{:^40}|{:^30}|{:^6}|{:^5}|{:^8}|",
                                     "ID", "ISBN", "Title", "Author", "Year", "Qty", "Rented"
                                     );
        std::string bar(header.length(), '-');
        bar[0] = '+';
        bar[bar.length() - 1] = '+';

        std::println("\n{}\n{}", bar, header);

        for (const auto& book : books) {
            book->print();
        }
        std::println("{}", bar);
        std::println("Found {} entries", books.size());

        std::cin.get();
    };

    auto func_create_book = [&db]() {
        std::string isbn, title, author, year, qty;

        std::println("\n\tAdding new book");

        std::cout << "ISBN: ";
        std::getline(std::cin, isbn);
        std::cout << "Title: ";
        std::getline(std::cin, title);
        std::cout << "Author: ";
        std::getline(std::cin, author);
        std::cout << "Year: ";
        std::getline(std::cin, year);
        std::cout << "QTY: ";
        std::getline(std::cin, qty);

        const Book newBook(-1, isbn, title, author, std::stoi(year), std::stoi(qty), 0);

        db->addBook(newBook);
        std::println("Successfully added new book");

        std::cin.get();
    };

    auto func_delete_book = [&db, &func_list_book]() {
        func_list_book();
        std::string input;

        std::cout << "Enter book index to delete, enter '0' to cancel: ";
        std::getline(std::cin, input);

        if (int idx = std::stoi(input); idx != 0) {
            db->removeBook(idx);
            std::println("Successfully removed book with id {}", idx);
        }

        std::cin.get();
    };

    auto func_list_user = [&db]() {
        const std::vector<std::unique_ptr<User>>& users = db->getUsers();
        std::string header = std::format("|{:^6}|{:^20}|{:^20}|{:^50}|",
                                     "ID", "Firstname", "Lastname", "Rented books"
                                     );
        std::string bar(header.length(), '-');
        bar[0] = '+';
        bar[bar.length() - 1] = '+';

        std::println("\n{}\n{}", bar, header);

        for (const auto& user : users) {
            user->print();
        }
        std::println("{}", bar);
        std::println("Found {} entries", users.size());

        std::cin.get();
    };
    /*
    *  =====================================================
    */

    /*
    *  ================= Create menu items =================
    */
    auto mainMenu = std::make_unique<MenuItem>("LibraX CLI", true);

    auto booksMenu = std::make_unique<MenuItem>("Books");
    booksMenu->addOption(std::make_unique<MenuOption>("List books", func_list_book));
    booksMenu->addOption(std::make_unique<MenuOption>("New book", func_create_book));
    booksMenu->addOption(std::make_unique<MenuOption>("Delete book", func_delete_book));

    auto usersMenu = std::make_unique<MenuItem>("Users");
    usersMenu->addOption(std::make_unique<MenuOption>("List users", func_list_user));

    auto settingsMenu = std::make_unique<MenuItem>("Settings");
    settingsMenu->addSubItem(std::make_unique<MenuItem>("-"));

    mainMenu->addSubItem(std::move(booksMenu));
    mainMenu->addSubItem(std::move(usersMenu));
    mainMenu->addSubItem(std::move(settingsMenu));
    /*
    *  =====================================================
    */

    // Display the main menu
    mainMenu->display();

    return 0;
}
