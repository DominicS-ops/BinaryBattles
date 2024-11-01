#ifndef GAMEUI_H
#define GAMEUI_H

#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <conio.h>   // For getch()
#include <windows.h> // For console size manipulation on Windows
#include <iostream>
#include <fstream>
#include <functional> // For std::function
#include <array> 
#include <filesystem>// For std::array
#include "game.h"

class GameUI 
{
public:
    GameUI(); // Constructor to initialize menu options
    void run();

private:
    void clearScreen() const;
    void displayMenu();
    void executeSelectedOption(); // New method for executing the action

    void getConsoleSize(int& rows, int& cols); // Add this line

    void displayScrollingText(const std::string& filename, int delayMs);

    void centerText(const std::string& text, int consoleWidth);

    void loadAndRunGame(const std::string& gamePath);


    struct MenuOption 
{
        std::string name;
        std::function<void()> action; // Function associated with the menu option
    };

    std::vector<MenuOption> options; // Use std::array for fixed size
    int selectedOption = 0; // Track selected option

    // Key definitions
    const char UP_ARROW = 72;   // ASCII code for UP arrow key
    const char DOWN_ARROW = 80; // ASCII code for DOWN arrow key
    const char ENTER_KEY = 13;  // ASCII code for ENTER key

    void startNewGame(); // Method to start a new game
    void loadGame();     // Method to load a game
    void exitGame();     // Method to exit the game
    void showCredits();  // Method to show credits
};

#endif // GAMEUI_H
