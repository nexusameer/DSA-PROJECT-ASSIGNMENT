#ifndef ADMINAPP_H
#define ADMINAPP_H

#include <string>
#include "AVLTree.h"  // Assuming AVLTree and WordNode are defined elsewhere

class AdminApp {
private:
    AVLTree dictionary;

    // Load words from file
    void loadFromFile(const std::string& filename);

    // Add backup functionality
    void createBackup(const std::string& filename);

    // Add validation
    bool validateWord(const std::string& word, const std::string& meaning);

public:
    AdminApp();

    void saveToFile(const std::string& filename);

    // Add a word to the dictionary
    void addWord();

    // Delete a word from the dictionary
    void deleteWord();

    // Display all words
    void displayWords();

    // Save and exit
    void saveAndExit();

    // Menu to interact with the admin app
    void run();
};

#endif
