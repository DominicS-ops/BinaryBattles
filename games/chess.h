#ifndef CHESS_H
#define CHESS_H

#include "game.h"  // Include the Game interface
#include "board.h" // Include the Board class
#include <iostream>

enum class Color { WHITE, BLACK };

class Chess : public Game {  // Inherit from Game
public:
    Chess();  // Constructor
    void run() override;  // Override the run function from the Game interface

private:
    void displayMenu();  // Function to display the game menu
    void startGame();    // Function to start the chess game
    void displayHelp();   // Function to display help information
    Board board;         // Board instance for the chess game
    Color currentPlayer; // Tracks the current player
};

#endif // CHESS_H
