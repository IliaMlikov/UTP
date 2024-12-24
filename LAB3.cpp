#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Book {
    string title;
    string author;
    int year;

 
    Book(string t, string a, int y) : title(t), author(a), year(y) {}

    void saveFile(ofstream& file) const {
        file << title << '\n' << author << '\n' << year << '\n';
    }


    void print() const {
        cout << "Title: " << title << ", Author: " << author << ", Year: " << year << endl;
    }
};

void addBook(const Book& book, const string& filename) {
    ofstream file(filename, ios::app);  
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }
    book.saveFile(file);
    file.close();
}

vector<Book> loadBooks(const string& filename) {
    vector<Book> books;
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file!" << endl;
        return books;
    }

    string title, author;
    int year;
    while (getline(file, title)) {
        getline(file, author);
        file >> year;
        file.ignore(); 
        books.push_back(Book(title, author, year));
    }

    file.close();
    return books;
}

void searchByTitle(const vector<Book>& books, const string& title) {
    bool found = false;
    for (const auto & book : books) {
        if (book.title == title) {
            book.print();
            found = true;
        }
    }
    if (!found) {
        cout << "No book found with the title: " << title << endl;
    }
}

bool comAuthor(const Book& a, const Book& b) {
    return a.author < b.author;
}

bool comYear(const Book& a, const Book& b) {
    return a.year < b.year;
}

void sortBooks(vector<Book>& books, int choice) {
    if (choice == 1) {
        sort(books.begin(), books.end(), comAuthor);
    } else if (choice == 2) {
        sort(books.begin(), books.end(), comYear);
    }
}

void filterYear(const vector<Book>& books, int year) {
    for (const auto& book : books) {
        if (book.year <= year) {
            book.print();
        }
    }
}

void ResultsToFile(const string& filename, const vector<Book>& books) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }

    for (const auto& book : books) {
        book.saveFile(file);
    }

    file.close();
}

void printMenu() {
    cout << "Menu:\n";
    cout << "1. Add a new book\n";
    cout << "2. Search book by title\n";
    cout << "3. Sort books\n";
    cout << "4. Filter books by year\n";
    cout << "5. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    const string filename = "books.txt";
    const string outputFilename = "output.txt";
    vector<Book> books = loadBooks(filename);

    while (true) {
        printMenu();
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string title, author;
            int year;

            cout << "Enter book title: ";
            getline(cin, title);
            if (title.empty()) break;

            cout << "Enter author: ";
            getline(cin, author);

            cout << "Enter year of publication: ";
            cin >> year;
            cin.ignore();

            Book newBook(title, author, year);
            addBook(newBook, filename);
            books.push_back(newBook);
        }
        else if (choice == 2) {
            string title;
            cout << "Enter book title to search: ";
            getline(cin, title);

            searchByTitle(books, title);
        }
        else if (choice == 3) {
            cout << "Sort by:\n";
            cout << "1. Author\n";
            cout << "2. Year\n";
            int sortChoice;
            cin >> sortChoice;
            cin.ignore();

            sortBooks(books, sortChoice);


            ResultsToFile(outputFilename, books);
            cout << "Books sorted and saved to " << outputFilename << endl;
        }
        else if (choice == 4) {
            int year;
            cout << "Enter a year: ";
            cin >> year;
            cin.ignore();

            filterYear(books, year);
        }
        else if (choice == 5) {
            cout << "Exiting program..." << endl;
            break;
        }
        else {
            cout << "Invalid choice, please try again." << endl;
        }
    }

    return 0;
}
