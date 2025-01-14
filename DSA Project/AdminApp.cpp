#include "AdminApp.h"
#include <iostream>
#include <fstream>

// Constructor definition
AdminApp::AdminApp(AVLTree& sharedTree) : AVLTree(sharedTree) {}

// Add a word to the AVL tree
void AdminApp::addWord(const std::string& word, const std::string& meaning) {
    WordNode newWord(word, meaning);
    insert(newWord);  // Use insert method from the base class
    std::cout << "Word added successfully." << std::endl;
}

// Delete a word from the AVL tree
void AdminApp::deleteWord(const std::string& word) {
    AVLTree::deleteWord(word);  // Use deleteWord method from the base class
    std::cout << "Word deleted successfully (if it existed)." << std::endl;
}

// Display all words in the dictionary
void AdminApp::displayAllWords() const {
    display();  // Call the display method from the base class to print all words
}

// Save the dictionary to a file
void AdminApp::saveDictionary(const std::string& filename) {
    saveToFile(filename);  // Call the saveToFile method from the base class
    std::cout << "Dictionary saved to " << filename << std::endl;
}
