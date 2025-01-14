#include <iostream>
#include "AVLTree.h"  // Include the header for AVLTree class
#include "User.h"     // Include the header for User class
#include "AdminApp.h" // Include the header for AdminApp class

// Function to display the main menu for the user
void displayUserMenu() {
    std::cout << "\nUser Menu:\n";
    std::cout << "1. Search for a Word\n";
    std::cout << "2. Display All Words\n";
    std::cout << "3. Exit\n";
    std::cout << "Enter your choice: ";
}

// Function to display the admin menu
void displayAdminMenu() {
    std::cout << "\nAdmin Menu:\n";
    std::cout << "1. Add Word\n";
    std::cout << "2. Delete Word\n";
    std::cout << "3. Display All Words\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    int roleChoice;

    std::cout << "Enter 1 for Admin Panel or 2 for User Panel: ";
    std::cin >> roleChoice;
    std::cin.ignore(); // To clear the buffer

    if (roleChoice == 1) {
        // Admin Panel
        AdminApp adminApp;
        adminApp.run(); // Run the admin app's functionality
    }
    else if (roleChoice == 2) {
        // User Panel
        AVLTree dictionary;  // Create an instance of the AVLTree for the user
        int userChoice;

        do {
            displayUserMenu();
            std::cin >> userChoice;
            std::cin.ignore();  // To clear the input buffer

            switch (userChoice) {
            case 1: {
                // Search for a word in the dictionary
                std::string word;
                std::cout << "Enter the word to search: ";
                std::getline(std::cin, word);
                dictionary.searchWord(word);
                break;
            }
            case 2: {
                // Display all words in the dictionary
                std::cout << "Displaying all words in the dictionary:\n";
                dictionary.display();
                break;
            }
            case 3:
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
            }
        } while (userChoice != 3);  // User panel continues until they choose to exit
    }
    else {
        std::cout << "Invalid choice. Exiting.\n";
    }

    return 0;
}
