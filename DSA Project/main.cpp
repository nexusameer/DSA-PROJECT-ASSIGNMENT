#include "AdminApp.h"
#include "User.h"
#include <iostream>

int main() {
    AVLTree sharedTree;  // Shared instance for admin and user operations

    AdminApp adminApp(sharedTree);  // Pass shared tree to AdminApp
    User userApp(sharedTree);       // Pass shared tree to User

    int mainChoice;

    do {
        std::cout << "\nMain Menu:\n";
        std::cout << "1. Admin Panel\n";
        std::cout << "2. User Panel\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> mainChoice;
        std::cin.ignore();

        switch (mainChoice) {
        case 1: {
            int adminChoice;
            std::string word, meaning;

            do {
                std::cout << "\nAdmin Menu:\n";
                std::cout << "1. Add Word\n";
                std::cout << "2. Delete Word\n";
                std::cout << "3. Display All Words\n";
                std::cout << "4. Save and Exit Admin Panel\n";
                std::cout << "Enter your choice: ";
                std::cin >> adminChoice;
                std::cin.ignore();

                switch (adminChoice) {
                case 1:
                    std::cout << "Enter word: ";
                    getline(std::cin, word);
                    std::cout << "Enter meaning: ";
                    getline(std::cin, meaning);
                    adminApp.addWord(word, meaning);
                    break;

                case 2:
                    std::cout << "Enter word to delete: ";
                    getline(std::cin, word);
                    adminApp.deleteWord(word);
                    break;

                case 3:
                    std::cout << "\nDictionary Words:\n";
                    adminApp.displayAllWords();
                    break;

                case 4:
                    adminApp.saveDictionary("dictionary.txt");
                    std::cout << "Dictionary saved. Exiting Admin Panel.\n";
                    break;

                default:
                    std::cout << "Invalid choice. Try again.\n";
                }

            } while (adminChoice != 4);
            break;
        }

        case 2: {
            int userChoice;
            std::string searchWord;

            do {
                std::cout << "\nUser Menu:\n";
                std::cout << "1. Search Word\n";
                std::cout << "2. Configure Search Settings\n";
                std::cout << "3. Exit User Panel\n";
                std::cout << "Enter your choice: ";
                std::cin >> userChoice;
                std::cin.ignore();

                switch (userChoice) {
                case 1:
                    std::cout << "Enter word to search: ";
                    getline(std::cin, searchWord);
                    userApp.searchAndSuggest(searchWord);
                    break;

                case 2: {
                    int maxSuggestions, threshold;
                    bool caseSensitive;
                    char caseChoice;

                    std::cout << "Enter maximum number of suggestions: ";
                    std::cin >> maxSuggestions;
                    std::cout << "Enter Levenshtein distance threshold: ";
                    std::cin >> threshold;
                    std::cout << "Case sensitive search? (y/n): ";
                    std::cin >> caseChoice;
                    std::cin.ignore();

                    caseSensitive = (caseChoice == 'y' || caseChoice == 'Y');
                    userApp.setSearchConfig(maxSuggestions, threshold, caseSensitive);
                    std::cout << "Search configuration updated.\n";
                    break;
                }

                case 3:
                    std::cout << "Exiting User Panel.\n";
                    break;

                default:
                    std::cout << "Invalid choice. Try again.\n";
                }

            } while (userChoice != 3);
            break;
        }

        case 3:
            std::cout << "Exiting application.\n";
            break;

        default:
            std::cout << "Invalid choice. Try again.\n";
        }

    } while (mainChoice != 3);

    return 0;
}
