#include "User.h"
#include <cstring>
#include <iostream>
#include <stdexcept>  // For exception handling


void User::loadDictionaryFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cout << "Failed to load dictionary file.\n";
        return;
    }

    std::string word, meaning;
    while (std::getline(inputFile, word) && std::getline(inputFile, meaning)) {
        WordNode wordNode(word, meaning);
        tree.insert(wordNode); // Insert into the AVLTree
    }
    inputFile.close();
}


// Set search configuration
void User::setSearchConfig(int maxSugg, int threshold, bool caseSens) {
    config.maxSuggestions = maxSugg;
    config.levenshteinThreshold = threshold;
    config.caseSensitive = caseSens;
}

// Function to calculate the Levenshtein distance
int User::levenshteinDistance(const std::string& s1, const std::string& s2) {
    int len1 = s1.length(), len2 = s2.length();
    std::vector<std::vector<int>> dp(len1 + 1, std::vector<int>(len2 + 1));

    for (int i = 0; i <= len1; i++) dp[i][0] = i;
    for (int j = 0; j <= len2; j++) dp[0][j] = j;

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            dp[i][j] = std::min({ dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost });
        }
    }

    return dp[len1][len2];
}

// Suggest words based on Levenshtein distance
void User::suggestWords(const std::string& searchWord) {
    std::vector<std::string> suggestions;
    int threshold = config.levenshteinThreshold;

    std::vector<std::string> allWords = tree.getAllWords();  // Call AVLTree method for words

    for (const auto& word : allWords) {
        if (levenshteinDistance(word, searchWord) <= threshold) {
            suggestions.push_back(word);
        }
    }

    if (suggestions.empty()) {
        std::cout << "No suggestions found.\n";
    }
    else {
        std::cout << "Suggestions for '" << searchWord << "':\n";
        for (size_t i = 0; i < suggestions.size() && i < static_cast<size_t>(config.maxSuggestions); ++i) {
            std::cout << suggestions[i] << "\n";
        }
    }
}

void User::searchAndSuggest(const std::string& wordToSearch) {
    // First, load the dictionary from the file if it isn't already loaded.
    if (tree.getAllWords().empty()) {
        loadDictionaryFromFile("dictionary.txt");
    }

    bool found = false;
    std::vector<std::string> allWords = tree.getAllWords();  // Get words from AVL tree

    for (const auto& word : allWords) {
        if ((config.caseSensitive ? word == wordToSearch
            : _stricmp(word.c_str(), wordToSearch.c_str()) == 0)) {
            std::cout << "Found: " << word << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Word not found.\n";
        suggestWords(wordToSearch);  // Provide suggestions based on Levenshtein distance
    }
}