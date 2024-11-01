#include "chess.h"

// Constructor
Chess::Chess() : currentPlayer(Color::WHITE) {}

void Chess::displayMenu() {
    std::cout << "=========================\n";
    std::cout << "        Chess Game       \n";
    std::cout << "=========================\n";
    std::cout << "1. Start Game\n";
    std::cout << "2. Help\n";
    std::cout << "3. Exit\n";
    std::cout << "=========================\n";
}

void Chess::startGame() {
    while (true) {
        board.printBoard();
        std::string start, end;

        // Provide clear instructions for the move
        std::cout << "Player " << (currentPlayer == Color::WHITE ? "White" : "Black")
                  << "'s turn.\n";
        std::cout << "Enter your move in algebraic notation (e.g., e2 e4).\n";
        std::cout << "For example: to move from e2 to e4, enter: e2 e4.\n";

        std::cin >> start >> end;

        if (board.movePiece(start, end)) {
            // Switch player after a valid move
            currentPlayer = (currentPlayer == Color::WHITE) ? Color::BLACK : Color::WHITE;
        }
    }
}

void Chess::displayHelp() {
    std::cout << "Chess is a strategic board game played between two players.\n";
    std::cout << "Each player starts with 16 pieces: 1 King, 1 Queen, 2 Rooks,\n";
    std::cout << "2 Knights, 2 Bishops, and 8 Pawns. The objective is to checkmate the opponent's King.\n";
    std::cout << "Players take turns moving one piece at a time using algebraic notation.\n";
}

void Chess::run() {
    int choice = 0;
    while (true) {
        displayMenu();
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Starting Chess Game...\n";
                startGame();
                break;
            case 2:
                displayHelp();
                break;
            case 3:
                std::cout << "Exiting to main menu...\n";
                return; // Exit back to the main menu
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

// Factory function to create the game instance
extern "C" Game* createGame() {
    return new Chess();
}
