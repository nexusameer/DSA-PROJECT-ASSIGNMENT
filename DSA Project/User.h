#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "AVLTree.h"  // Assuming AVLTree and WordNode are defined elsewhere

class User : public AVLTree {  // Inherit from AVLTree
private:
    struct SearchConfig {
        int maxSuggestions = 5;
        int levenshteinThreshold = 2;
        bool caseSensitive = false;
    } config;

    // Function to calculate the Levenshtein distance between two strings
    int levenshteinDistance(const std::string& s1, const std::string& s2);

    // Suggest words based on Levenshtein distance (words within a threshold)
    void suggestWords(const std::string& searchWord);

public:
    User();  // Constructor

    void setSearchConfig(int maxSugg, int threshold, bool caseSens);

    // Function to search for a word and suggest similar words if not found
    void searchAndSuggest(const std::string& searchWord);
};

#endif
