#include "board.h"
#include <iostream>
#include <iomanip>  // For std::setw>
#include <cctype>   // For std::toupper>

Board::Board() : board(8, std::vector<char>(8, ' ')) {
    // Initialize the board with pieces
    board[0][0] = 'R'; board[0][7] = 'R'; // White Rooks
    board[0][1] = 'N'; board[0][6] = 'N'; // White Knights
    board[0][2] = 'B'; board[0][5] = 'B'; // White Bishops
    board[0][3] = 'Q'; // White Queen
    board[0][4] = 'K'; // White King
    for (int col = 0; col < 8; ++col) {
        board[1][col] = 'P'; // White Pawns
        board[6][col] = 'p'; // Black Pawns
    }
    board[7][0] = 'r'; board[7][7] = 'r'; // Black Rooks
    board[7][1] = 'n'; board[7][6] = 'n'; // Black Knights
    board[7][2] = 'b'; board[7][5] = 'b'; // Black Bishops
    board[7][3] = 'q'; // Black Queen
    board[7][4] = 'k'; // Black King
}

// Function to print the current state of the board
void Board::printBoard() const {
    std::cout << "  a b c d e f g h\n"; // Column labels
    std::cout << "  -----------------\n"; // Separator
    for (int row = 0; row < 8; ++row) {
        std::cout << 8 - row << "| "; // Row labels
        for (const auto& cell : board[row]) {
            std::cout << std::setw(2) << cell << " "; // Aligning pieces
        }
        std::cout << " |" << (8 - row) << "\n"; // End of row
    }
    std::cout << "  -----------------\n"; // Bottom separator
    std::cout << "  a b c d e f g h\n"; // Column labels again
}

// Function to move a piece using algebraic notation
bool Board::movePiece(const std::string& start, const std::string& end) {
    int startRow = 8 - (start[1] - '0'); // Convert from chess row to index
    int startCol = start[0] - 'a';       // Convert from chess column to index
    int endRow = 8 - (end[1] - '0');     // Convert from chess row to index
    int endCol = end[0] - 'a';           // Convert from chess column to index

    if (startRow >= 0 && startRow < 8 && startCol >= 0 && startCol < 8 &&
        endRow >= 0 && endRow < 8 && endCol >= 0 && endCol < 8 &&
        board[startRow][startCol] != ' ') {
        board[endRow][endCol] = board[startRow][startCol]; // Move piece
        board[startRow][startCol] = ' '; // Clear old position
        return true; // Move was successful
    }
    std::cout << "Invalid move, try again.\n";
    return false; // Move failed
}
