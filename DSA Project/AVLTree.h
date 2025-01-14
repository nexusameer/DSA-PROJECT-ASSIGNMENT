#ifndef AVLTREE_H
#define AVLTREE_H

#include <string>
#include <vector>
#include "WordNode.h"  // Assuming WordNode is defined elsewhere

class AVLTree {
private:
    struct Node {
        WordNode data;
        Node* left;
        Node* right;
        int height;

        Node(const WordNode& wordData);
    };

    Node* root;

    // Helper functions
    int getHeight(Node* node);
    int getBalanceFactor(Node* node);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* insert(Node* node, const WordNode& data);
    Node* findMinValueNode(Node* node);
    Node* deleteNode(Node* root, const std::string& word);
    void inorderDisplay(Node* node);
    void saveToFileRecursive(Node* node, std::ofstream& outputFile);
    void inorderWords(Node* node, std::vector<std::string>& words);

public:
    AVLTree();

    void insert(const WordNode& data);
    void deleteWord(const std::string& word);
    void display();
    void saveToFile(std::ofstream& outputFile);
    void searchWord(const std::string& word);
    std::vector<std::string> getAllWords();
};

#endif
