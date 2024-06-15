#include "util/menu/MenuItem.h"
#include "util/screen/Screen.h"
#include "util/sql/Database.h"

// TODO: REFACTOR AND CREATE SEPARATE CLASS FOR INLINE FUNCTIONS
int main() {
    // Create database connection
    auto* db = new Database();

    /*
    *  ========== Create functions for MenuOption ==========
    */
    auto func_list_book = [&db]() {
        const std::vector<Book*> books = db->getBooks();
        std::string header = std::format("|{:^6}|{:^20}|{:^40}|{:^30}|{:^6}|{:^5}|{:^8}|",
                                     "ID", "ISBN", "Title", "Author", "Year", "Qty", "Rented"
                                     );
        std::string bar(header.length(), '-');
        bar[0] = '+';
        bar[bar.length() - 1] = '+';

        std::println("\n{}\n{}", bar,header);

        for(auto const book: books) {
            book->print();
        }
        std::println("{}", bar);
        std::println("Found {} entries", books.size());

        std::cin.get();
    };

    auto func_create_book = [&db]() {
        std::string isbn, title, author, year, qty;

        std::println("\n\tAdding new book");

        std::print("ISBN: ");
        std::getline(std::cin, isbn);
        std::print("Title: ");
        std::getline(std::cin, title);
        std::print("Author: ");
        std::getline(std::cin, author);
        std::print("Year: ");
        std::getline(std::cin, year);
        std::print("QTY: ");
        std::getline(std::cin, qty);

        const Book newBook(-1, isbn, title, author, std::stoi(year), std::stoi(qty), 0);

        db->addBook(newBook);
        std::println("Successfully added new book");

        std::cin.get();
    };

    auto func_delete_book = [&db, &func_list_book]() {
        func_list_book();
        std::string input;

        std::print("Enter book index to delete, enter '0' to cancel: ");
        std::getline(std::cin, input);

        if(int idx = stoi(input); idx != 0) {
            db->removeBook(idx);
            std::println("Successfully removed book with id {}", idx);
        }

        std::cin.get();
    };
    /*
    *  =====================================================
    */

    /*
    *  ================= Create menu items =================
    */
    auto* mainMenu = new MenuItem("LibraX CLI", true);

    auto* booksMenu = new MenuItem("Books");
    booksMenu->addOption(new MenuOption("List books", func_list_book));
    booksMenu->addOption(new MenuOption("New book", func_create_book));
    booksMenu->addOption(new MenuOption("Delete book", func_delete_book));

    //booksMenu->addSubItem(new MenuItem("[NOT IMPLEMENTED] Search"));
    //booksMenu->addSubItem(new MenuItem("[NOT IMPLEMENTED] Edit book"));

    auto* usersMenu = new MenuItem("Users");
    usersMenu->addSubItem(new MenuItem("[NOT IMPLEMENTED] List users"));
    usersMenu->addSubItem(new MenuItem("[NOT IMPLEMENTED] Search"));
    usersMenu->addSubItem(new MenuItem("[NOT IMPLEMENTED] Create user"));
    usersMenu->addSubItem(new MenuItem("[NOT IMPLEMENTED] Edit user"));
    usersMenu->addSubItem(new MenuItem("[NOT IMPLEMENTED] Delete user"));

    auto* settingsMenu = new MenuItem("Settings");
    settingsMenu->addSubItem(new MenuItem("-"));

    mainMenu->addSubItem(booksMenu);
    mainMenu->addSubItem(usersMenu);
    mainMenu->addSubItem(settingsMenu);
    /*
    *  =====================================================
    */

    // Display the main menu
    mainMenu->display();

    delete booksMenu;
    delete usersMenu;
    delete settingsMenu;
    delete mainMenu;
    delete db;

    return 0;
}