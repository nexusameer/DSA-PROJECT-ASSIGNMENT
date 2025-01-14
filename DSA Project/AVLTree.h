// AVLTree.h
#ifndef AVLTREE_H
#define AVLTREE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "WordNode.h"

class AVLTree {
protected:
    struct Node {
        WordNode data;
        Node* left;
        Node* right;
        int height;

        Node(const WordNode& wordData) : data(wordData), left(nullptr), right(nullptr), height(1) {}
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
    void inorderDisplay(Node* node) const;
    void saveToFileRecursive(Node* node, std::ofstream& outputFile) const;
    void inorderWords(Node* node, std::vector<std::string>& words) const;

public:
    AVLTree();

    void insert(const WordNode& data);
    void deleteWord(const std::string& word);
    void display() const;
    void saveToFile(const std::string& filename) const;
    void searchWord(const std::string& word) const;
    std::vector<std::string> getAllWords() const;
};
#endif 