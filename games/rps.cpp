#include "Rps.h"

// Function to create an instance of the RPSGame
extern "C" Game* createGame() {
    return new RPSGame();
}

void RPSGame::run() {
    displayMenu();
}

void RPSGame::displayMenu() {
    int choice = 0;

    while (true) {
        std::cout << "\nRock-Paper-Scissors Menu:\n";
        std::cout << "1. Start Game\n";
        std::cout << "2. Help\n";
        std::cout << "3. Exit\n";
        std::cout << "Choose an option (1-3): ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                startGame();
                break;
            case 2:
                displayHelp();
                break;
            case 3:
                std::cout << "Exiting to main menu...\n";
                return;  // Exit back to the two-player menu
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    }
}

void RPSGame::startGame() {
    std::string options[3] = {"Rock", "Paper", "Scissors"};
    std::string userChoice;
    std::string computerChoice;
    int userScore = 0;
    int computerScore = 0;
    int rounds = 0;

    std::cout << "Starting the game...\n";
    std::cout << "Type 'exit' at any time to return to the menu.\n";

    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(0)));

    while (true) {
        std::cout << "\nChoose Rock, Paper, or Scissors: ";
        std::cin >> userChoice;

        // Exit if the user types 'exit'
        if (userChoice == "exit") {
            std::cout << "Exiting to menu...\n";
            return; // Exit back to the menu
        }

        // Validate user input
        if (userChoice != "Rock" && userChoice != "Paper" && userChoice != "Scissors") {
            std::cout << "Invalid choice, please try again.\n";
            continue; // Prompt again for valid input
        }

        // Generate computer's choice
        int randomIndex = std::rand() % 3; // Random number between 0 and 2
        computerChoice = options[randomIndex];

        std::cout << "Computer chose: " << computerChoice << "\n";

        // Determine the winner
        if (userChoice == computerChoice) {
            std::cout << "It's a tie!\n";
        } else if ((userChoice == "Rock" && computerChoice == "Scissors") ||
                   (userChoice == "Scissors" && computerChoice == "Paper") ||
                   (userChoice == "Paper" && computerChoice == "Rock")) {
            std::cout << "You win this round!\n";
            userScore++;
        } else {
            std::cout << "Computer wins this round!\n";
            computerScore++;
        }

        rounds++;
        std::cout << "Score: You " << userScore << " - " << computerScore << " Computer\n";
    }
}

void RPSGame::displayHelp() {
    std::cout << "\nHelp: Rock-Paper-Scissors\n";
    std::cout << "In this game, you will play against another player.\n";
    std::cout << "Choose Rock, Paper, or Scissors. The rules are:\n";
    std::cout << " - Rock beats Scissors\n";
    std::cout << " - Scissors beats Paper\n";
    std::cout << " - Paper beats Rock\n";
    std::cout << "The game continues until a player decides to exit.\n";
}
