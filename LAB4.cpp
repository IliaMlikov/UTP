#include <iostream>
#include <pqxx/pqxx>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <ctime>

using namespace std;
using namespace pqxx;

class Author {
public:
    int id;
    string name;
    int birth_year;

    Author(int id, const string& name, int birth_year)
        : id(id), name(name), birth_year(birth_year) {}

    static void addAuthor(transaction_base& txn, const Author& author) {
        string query = "INSERT INTO authors (name, birth_year) VALUES (" + txn.quote(author.name) + ", " + to_string(author.birth_year) + ")";
        txn.exec(query);
    }
};

class Book {
public:
    int id;
    string title;
    int author_id;
    int publication_year;
    string genre;

    Book(int id, const string& title, int author_id, int publication_year, const string& genre)
        : id(id), title(title), author_id(author_id), publication_year(publication_year), genre(genre) {}

    static void addBook(transaction_base& txn, const Book& book) {
        string query = "INSERT INTO books (title, author_id, publication_year, genre) VALUES (" 
                       + txn.quote(book.title) + ", " + to_string(book.author_id) + ", "
                       + to_string(book.publication_year) + ", " + txn.quote(book.genre) + ")";
        txn.exec(query);
    }
};


class User {
public:
    int id;
    string name;
    string registration_date;

    User(int id, const string& name, const string& registration_date)
        : id(id), name(name), registration_date(registration_date) {}

    static void addUser(transaction_base& txn, const User& user) {
        string query = "INSERT INTO users (name, registration_date) VALUES (" + txn.quote(user.name) + ", " + txn.quote(user.registration_date) + ")";
        txn.exec(query);
    }
};


class BorrowedBook {
public:
    int user_id;
    int book_id;
    string borrow_date;
    string return_date;

    BorrowedBook(int user_id, int book_id, const string& borrow_date, const string& return_date)
        : user_id(user_id), book_id(book_id), borrow_date(borrow_date), return_date(return_date) {}

    // Зарегистрировать заём книги
    static void borrowBook(transaction_base& txn, const BorrowedBook& borrowedBook) {
        string query = "INSERT INTO borrowed_books (user_id, book_id, borrow_date, return_date) VALUES (" 
                       + to_string(borrowedBook.user_id) + ", " + to_string(borrowedBook.book_id) + ", "
                       + txn.quote(borrowedBook.borrow_date) + ", " + txn.quote(borrowedBook.return_date) + ")";
        txn.exec(query);
    }
};

template<typename T1, typename T2>
class Pair {
public:
    T1 first;
    T2 second;

    Pair(const T1& first, const T2& second) : first(first), second(second) {}
};

void logAction(const string& action) {
    ofstream logFile("log.txt", ios_base::app);
    if (logFile.is_open()) {
        time_t now = time(0);
        char* dt = ctime(&now);
        logFile << "[" << dt << "] " << action << endl;
        logFile.close();
    }
}

class Library {
private:
    connection* conn;
    string conn_str = "dbname=library user=postgres password=yourpassword host=localhost port=5432";

public:
    Library() {
        try {
            conn = new connection(conn_str);
            if (conn->is_open()) {
                cout << "Opened database successfully: " << conn->dbname() << endl;
            } else {
                cout << "Can't open database" << endl;
            }
        } catch (const std::exception& e) {
            cerr << e.what() << std::endl;
        }
    }

    ~Library() {
        conn->close();
        delete conn;
    }

    void addAuthor(const Author& author) {
        try {
            work txn(*conn);
            Author::addAuthor(txn, author);
            txn.commit();
            logAction("Added author: " + author.name);
        } catch (const sql_error& e) {
            cerr << e.what() << endl;
        }
    }

    void addBook(const Book& book) {
        try {
            work txn(*conn);
            Book::addBook(txn, book);
            txn.commit();
            logAction("Added book: " + book.title);
        } catch (const sql_error& e) {
            cerr << e.what() << endl;
        }
    }

    void addUser(const User& user) {
        try {
            work txn(*conn);
            User::addUser(txn, user);
            txn.commit();
            logAction("Added user: " + user.name);
        } catch (const sql_error& e) {
            cerr << e.what() << endl;
        }
    }

    void borrowBook(const BorrowedBook& borrowedBook) {
        try {
            work txn(*conn);
            BorrowedBook::borrowBook(txn, borrowedBook);
            txn.commit();
            logAction("Book borrowed by user: " + to_string(borrowedBook.user_id));
        } catch (const sql_error& e) {
            cerr << e.what() << endl;
        }
    }

    void listBooksByAuthor(int author_id) {
        try {
            work txn(*conn);
            string query = "SELECT title FROM books WHERE author_id = " + to_string(author_id);
            result res = txn.exec(query);
            for (auto row : res) {
                cout << "Book Title: " << row["title"].as<string>() << endl;
            }
        } catch (const sql_error& e) {
            cerr << e.what() << endl;
        }
    }
};

int main() {
    Library library;

    while (true) {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Author\n";
        cout << "2. Add Book\n";
        cout << "3. Add User\n";
        cout << "4. Borrow Book\n";
        cout << "5. List Books by Author\n";
        cout << "6. Exit\n";
        cout << "Choose an option: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            string name;
            int birth_year;
            cout << "Enter author's name: ";
            cin >> name;
            cout << "Enter author's birth year: ";
            cin >> birth_year;
            library.addAuthor(Author(0, name, birth_year));
        } else if (choice == 2) {
            string title, genre;
