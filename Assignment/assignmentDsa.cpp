#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>
#include <vector>
#include <sstream>
using namespace std;

class Book {
private:
    string isbn;
    string title;
    string author;
    string publisher;
    string genre;

public:
    Book() {}

    Book(const string& isbn, const string& title, const string& author, const string& publisher, const string& genre) {
        this->isbn = isbn;
        this->title = title;
        this->author = author;
        this->publisher = publisher;
        this->genre = genre;
    }

    string getISBN() const { return isbn; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getPublisher() const { return publisher; }
    string getGenre() const { return genre; }

    void display() const {
        cout << "ISBN: " << isbn << "\n";
        cout << "Title: " << title << "\n";
        cout << "Author: " << author << "\n";
        cout << "Publisher: " << publisher << "\n";
        cout << "Genre: " << genre << "\n";
    }
};

unordered_map<string, Book> primaryHashTable;
unordered_map<string, set<string>> titleIndex;
unordered_map<string, set<string>> authorIndex;

vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void loadLibraryData(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        vector<string> fields = split(line, ';');
        if (fields.size() < 5) continue;

        Book book(fields[0], fields[1], fields[2], fields[3], fields[4]);

        primaryHashTable[book.getISBN()] = book;

        titleIndex[book.getTitle()].insert(book.getISBN());

        authorIndex[book.getAuthor()].insert(book.getISBN());
    }

    file.close();
}

void searchByISBN(const string& isbn) {
    int nodesChecked = 0;
    if (primaryHashTable.find(isbn) != primaryHashTable.end()) {
        nodesChecked++;
        const Book& book = primaryHashTable[isbn];
        cout << "Book Found:\n";
        book.display();
    }
    else {
        cout << "No book found with ISBN: " << isbn << endl;
    }
    cout << "Nodes checked: " << nodesChecked << endl;
}

void searchByTitle(const string& title) {
    int nodesChecked = 0;
    if (titleIndex.find(title) != titleIndex.end()) {
        nodesChecked++;
        cout << "Books Found:\n";
        for (const string& isbn : titleIndex[title]) {
            nodesChecked++;
            const Book& book = primaryHashTable[isbn];
            book.display();
        }
    }
    else {
        cout << "No books found with title: " << title << endl;
    }
    cout << "Nodes checked: " << nodesChecked << endl;
}

void searchByAuthor(const string& author) {
    int nodesChecked = 0;
    if (authorIndex.find(author) != authorIndex.end()) {
        nodesChecked++;
        cout << "Books Found:\n";
        for (const string& isbn : authorIndex[author]) {
            nodesChecked++;
            const Book& book = primaryHashTable[isbn];
            book.display();
        }
    }
    else {
        cout << "No books found with author: " << author << endl;
    }
    cout << "Nodes checked: " << nodesChecked << endl;
}

int main() {
    string filename = "books-dataset.txt";
    loadLibraryData(filename);

    int choice;
    string query;

    do {
        cout << "\nLibrary Search System:\n";
        cout << "1. Search by ISBN\n";
        cout << "2. Search by Title\n";
        cout << "3. Search by Author\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Enter ISBN: ";
            getline(cin, query);
            searchByISBN(query);
            break;
        case 2:
            cout << "Enter Title: ";
            getline(cin, query);
            searchByTitle(query);
            break;
        case 3:
            cout << "Enter Author: ";
            getline(cin, query);
            searchByAuthor(query);
            break;
        case 4:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}