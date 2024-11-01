#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string> // Include for std::string

class Board {
public:
    Board();  // Constructor to initialize the board
    void printBoard() const;  // Function to print the current state of the board
    bool movePiece(const std::string& start, const std::string& end); // Function to move a piece using algebraic notation

private:
    std::vector<std::vector<char>> board;  // 2D vector to represent the board
};

#endif // BOARD_H
