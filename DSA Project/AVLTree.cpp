#include "AVLTree.h"
#include <iostream>
#include <fstream>
#include <algorithm>  // For std::max

// Node Constructor
AVLTree::Node::Node(const WordNode& wordData)
    : data(wordData), left(nullptr), right(nullptr), height(1) {}

// Constructor
AVLTree::AVLTree() : root(nullptr) {}

// Helper function to get height of a node
int AVLTree::getHeight(Node* node) {
    return node == nullptr ? 0 : node->height;
}

// Helper function to get the balance factor of a node
int AVLTree::getBalanceFactor(Node* node) {
    return node == nullptr ? 0 : getHeight(node->left) - getHeight(node->right);
}

// Rotate right (for left-heavy trees)
AVLTree::Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Rotate left (for right-heavy trees)
AVLTree::Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Insert function with balancing logic
AVLTree::Node* AVLTree::insert(Node* node, const WordNode& data) {
    // Perform standard BST insertion
    if (node == nullptr)
        return new Node(data);

    if (data.word < node->data.word)
        node->left = insert(node->left, data);
    else if (data.word > node->data.word)
        node->right = insert(node->right, data);
    else
        return node;  // Duplicate words are not allowed

    // Update height of this ancestor node
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    // Get the balance factor and balance the node
    int balance = getBalanceFactor(node);

    // Left Left Case
    if (balance > 1 && data.word < node->left->data.word)
        return rotateRight(node);

    // Right Right Case
    if (balance < -1 && data.word > node->right->data.word)
        return rotateLeft(node);

    // Left Right Case
    if (balance > 1 && data.word > node->left->data.word) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left Case
    if (balance < -1 && data.word < node->right->data.word) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Find the node with the minimum value
AVLTree::Node* AVLTree::findMinValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != nullptr)
        current = current->left;
    return current;
}

// Delete a word from the AVL tree
AVLTree::Node* AVLTree::deleteNode(Node* root, const std::string& word) {
    if (root == nullptr)
        return root;

    // Perform standard BST deletion
    if (word < root->data.word)
        root->left = deleteNode(root->left, word);
    else if (word > root->data.word)
        root->right = deleteNode(root->right, word);
    else {
        // Node with only one child or no child
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node* temp = root->left ? root->left : root->right;

            // No child case
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            }
            else  // One child case
                *root = *temp;  // Copy the contents of the non-empty child
            delete temp;
        }
        else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            Node* temp = findMinValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->data = temp->data;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->data.word);
        }
    }

    // If the tree had only one node then return
    if (root == nullptr)
        return root;

    // Update height of the current node
    root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

    // Get balance factor and balance the node
    int balance = getBalanceFactor(root);

    // Left Left Case
    if (balance > 1 && getBalanceFactor(root->left) >= 0)
        return rotateRight(root);

    // Left Right Case
    if (balance > 1 && getBalanceFactor(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Right Right Case
    if (balance < -1 && getBalanceFactor(root->right) <= 0)
        return rotateLeft(root);

    // Right Left Case
    if (balance < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// In-order traversal to display the tree
void AVLTree::inorderDisplay(Node* node) {
    if (node != nullptr) {
        inorderDisplay(node->left);
        std::cout << node->data.word << ": " << node->data.meaning << std::endl;
        inorderDisplay(node->right);
    }
}

// Helper function to save the tree to a file
void AVLTree::saveToFileRecursive(Node* node, std::ofstream& outputFile) {
    if (node != nullptr) {
        outputFile << node->data.word << std::endl;
        outputFile << node->data.meaning << std::endl;
        saveToFileRecursive(node->left, outputFile);
        saveToFileRecursive(node->right, outputFile);
    }
}

// In-order traversal to gather all words in the AVL tree
void AVLTree::inorderWords(Node* node, std::vector<std::string>& words) {
    if (node != nullptr) {
        inorderWords(node->left, words);
        words.push_back(node->data.word);  // Add word to the list
        inorderWords(node->right, words);
    }
}

// Public method to insert a word
void AVLTree::insert(const WordNode& data) {
    root = insert(root, data);
}

// Public method to delete a word
void AVLTree::deleteWord(const std::string& word) {
    root = deleteNode(root, word);
}

// Public method to display all words in the tree
void AVLTree::display() {
    inorderDisplay(root);
}

// Public method to save the dictionary to a file
void AVLTree::saveToFile(std::ofstream& outputFile) {
    if (outputFile.is_open()) {
        saveToFileRecursive(root, outputFile);
    }
    else {
        std::cout << "Error saving dictionary to file.\n";
    }
}

// Public method to search for a word
void AVLTree::searchWord(const std::string& word) {
    Node* current = root;
    while (current != nullptr) {
        if (word == current->data.word) {
            std::cout << "Found: " << current->data.word << " - " << current->data.meaning << std::endl;
            return;
        }
        else if (word < current->data.word) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    std::cout << "Word not found.\n";
}

// Public method to get all words from the tree
std::vector<std::string> AVLTree::getAllWords() {
    std::vector<std::string> words;
    inorderWords(root, words);
    return words;
}
