#include "User.h"
#include <iostream>
#include <stdexcept>  // For exception handling

// Constructor
User::User() {
    // Initialize configuration if necessary
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

    std::vector<std::string> allWords = getAllWords();  // Call inherited AVLTree function

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
        for (const auto& word : suggestions) {
            std::cout << word << "\n";
        }
    }
}

void User::searchAndSuggest(const std::string& wordToSearch) {
    std::cout << "Searching for the word: " << wordToSearch << std::endl;

    bool found = searchWord(wordToSearch);  // Assuming `searchWord` now returns a bool

    if (!found) {
        std::cout << "Word not found.\n";
        std::cout << "\nIf you meant one of the following, try again:\n";
        suggestWords(wordToSearch);
    }
    else {
        std::cout << "Word found.\n";
    }
}
