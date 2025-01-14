
#include <string>
#include <iostream>
#include <string>

using namespace std;


class WordNode {
public:
    string word;
    string meaning;
    // Add validation and constructor improvements
    WordNode(string w, string m) {
        if (w.empty()) {
            throw invalid_argument("Word cannot be empty");
        }
        word = std::move(w);
        meaning = std::move(m);
    }

    // Add useful methods
    bool isEmpty() const {
        return word.empty() || meaning.empty();
    }
};
