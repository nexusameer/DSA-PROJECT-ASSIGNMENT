#include "AdminApp.h"
#include <iostream>
#include <fstream>
#include <stdexcept>  // For exception handling

// Constructor
AdminApp::AdminApp() {
    loadFromFile("dictionary.txt");  // Load dictionary data on startup
}

// Load words from file
void AdminApp::loadFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (inputFile.is_open()) {
        std::string word, meaning;
        while (getline(inputFile, word)) {
            getline(inputFile, meaning);
            WordNode wordNode(word, meaning);
            dictionary.insert(wordNode);
        }
        inputFile.close();
    }
}

// Add backup functionality
void AdminApp::createBackup(const std::string& filename) {
    std::string backupFile = filename + ".backup";
    saveToFile(backupFile);
}

// Add validation
bool AdminApp::validateWord(const std::string& word, const std::string& meaning) {
    return !word.empty() && !meaning.empty() &&
        word.length() <= 100 && meaning.length() <= 1000;
}

// Save the dictionary to a file
void AdminApp::saveToFile(const std::string& filename) {
    try {
        std::ofstream outputFile(filename, std::ios::out | std::ios::binary);
        if (!outputFile) {
            throw std::runtime_error("Cannot open file for writing: " + filename);
        }
        dictionary.saveToFile(outputFile);
        outputFile.close();
    }
    catch (const std::exception& e) {
        std::cerr << "Error saving file: " << e.what() << std::endl;
        createBackup(filename);  // Attempt to create a backup
    }
}

// Add a word to the dictionary
void AdminApp::addWord() {
    std::string word, meaning;
    std::cout << "Enter word: ";
    std::getline(std::cin, word);
    std::cout << "Enter meaning: ";
    std::getline(std::cin, meaning);

    WordNode wordNode(word, meaning);
    dictionary.insert(wordNode);

    std::cout << "Word added successfully." << std::endl;
}

// Delete a word from the dictionary
void AdminApp::deleteWord() {
    std::string word;
    std::cout << "Enter word to delete: ";
    std::getline(std::cin, word);

    dictionary.deleteWord(word);

    std::cout << "Word deleted successfully (if it existed)." << std::endl;
}

// Display all words in the dictionary
void AdminApp::displayWords() {
    std::cout << "All words in the dictionary:\n";
    dictionary.display();
}

// Save the dictionary and exit
void AdminApp::saveAndExit() {
    saveToFile("dictionary.txt");
    std::cout << "Dictionary saved. Exiting." << std::endl;
}

// Menu to interact with the admin app
void AdminApp::run() {
    int choice;
    do {
        std::cout << "\nAdmin Menu:\n";
        std::cout << "1. Add Word\n";
        std::cout << "2. Delete Word\n";
        std::cout << "3. Display All Words\n";
        std::cout << "4. Save & Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();  // To clear the buffer

        switch (choice) {
        case 1:
            addWord();
            break;
        case 2:
            deleteWord();
            break;
        case 3:
            displayWords();
            break;
        case 4:
            saveAndExit();
            break;
        default:
            std::cout << "Invalid choice. Try again." << std::endl;
        }
    } while (choice != 4);
}
