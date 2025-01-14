// WordNode.h
#ifndef WORDNODE_H
#define WORDNODE_H

#include <string>
#include <stdexcept>

class WordNode {
public:
    std::string word;
    std::string meaning;

    // Constructor with validation
    WordNode(const std::string& w, const std::string& m) {
        if (w.empty()) {
            throw std::invalid_argument("Word cannot be empty");
        }
        word = w;
        meaning = m;
    }

    bool isEmpty() const {
        return word.empty() || meaning.empty();
    }
};

#endif  // WORDNODE_H