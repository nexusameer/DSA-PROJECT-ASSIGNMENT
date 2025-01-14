#ifndef ADMINAPP_H
#define ADMINAPP_H

#include "AVLTree.h"

class AdminApp : public AVLTree {
public:
    AdminApp(AVLTree& sharedTree); // Constructor declaration

    void addWord(const std::string& word, const std::string& meaning);  // Function declarations
    void deleteWord(const std::string& word);
    void displayAllWords() const;
    void saveDictionary(const std::string& filename);
};

#endif  // ADMINAPP_H
