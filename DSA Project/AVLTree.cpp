// AVLTree.cpp
#include "AVLTree.h"
#include <algorithm>

AVLTree::AVLTree() : root(nullptr) {}

int AVLTree::getHeight(Node* node) {
    return node == nullptr ? 0 : node->height;
}

int AVLTree::getBalanceFactor(Node* node) {
    return node == nullptr ? 0 : getHeight(node->left) - getHeight(node->right);
}

AVLTree::Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

AVLTree::Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

AVLTree::Node* AVLTree::insert(Node* node, const WordNode& data) {
    if (node == nullptr) return new Node(data);
    if (data.word < node->data.word)
        node->left = insert(node->left, data);
    else if (data.word > node->data.word)
        node->right = insert(node->right, data);
    else
        return node;

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    int balance = getBalanceFactor(node);

    if (balance > 1 && data.word < node->left->data.word)
        return rotateRight(node);
    if (balance < -1 && data.word > node->right->data.word)
        return rotateLeft(node);
    if (balance > 1 && data.word > node->left->data.word) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && data.word < node->right->data.word) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

AVLTree::Node* AVLTree::deleteNode(Node* root, const std::string& word) {
    if (root == nullptr) return root;
    if (word < root->data.word)
        root->left = deleteNode(root->left, word);
    else if (word > root->data.word)
        root->right = deleteNode(root->right, word);
    else {
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            }
            else {
                *root = *temp;
            }
            delete temp;
        }
        else {
            Node* temp = findMinValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data.word);
        }
    }
    if (root == nullptr) return root;

    root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
    int balance = getBalanceFactor(root);

    if (balance > 1 && getBalanceFactor(root->left) >= 0)
        return rotateRight(root);
    if (balance > 1 && getBalanceFactor(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && getBalanceFactor(root->right) <= 0)
        return rotateLeft(root);
    if (balance < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

AVLTree::Node* AVLTree::findMinValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != nullptr)
        current = current->left;
    return current;
}

void AVLTree::inorderDisplay(Node* node) const {
    if (node != nullptr) {
        inorderDisplay(node->left);
        std::cout << node->data.word << ": " << node->data.meaning << std::endl;
        inorderDisplay(node->right);
    }
}

void AVLTree::saveToFileRecursive(Node* node, std::ofstream& outputFile) const {
    if (node != nullptr) {
        outputFile << node->data.word << '\n' << node->data.meaning << '\n';
        saveToFileRecursive(node->left, outputFile);
        saveToFileRecursive(node->right, outputFile);
    }
}

void AVLTree::inorderWords(Node* node, std::vector<std::string>& words) const {
    if (node != nullptr) {
        inorderWords(node->left, words);
        words.push_back(node->data.word);
        inorderWords(node->right, words);
    }
}

void AVLTree::insert(const WordNode& data) {
    root = insert(root, data);
}

void AVLTree::deleteWord(const std::string& word) {
    root = deleteNode(root, word);
}

void AVLTree::display() const {
    inorderDisplay(root);
}

void AVLTree::saveToFile(const std::string& filename) const {
    std::ofstream outputFile(filename);
    if (outputFile.is_open()) {
        saveToFileRecursive(root, outputFile);
        outputFile.close();
    }
    else {
        std::cerr << "Error saving dictionary to file." << std::endl;
    }
}

void AVLTree::searchWord(const std::string& word) const {
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
    std::cout << "Word not found." << std::endl;
}

std::vector<std::string> AVLTree::getAllWords() const {
    std::vector<std::string> words;
    inorderWords(root, words);
    return words;
}
