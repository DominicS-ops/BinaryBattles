
#include "GameUI.h"

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

GameUI::GameUI() : selectedOption(0)
{
    options.push_back({ "Start Game", [this]() { startNewGame(); } });
    options.push_back({ "Load Game", [this]() { loadGame(); } });
    options.push_back({ "Credits", [this]() { showCredits(); } });
    options.push_back({ "Exit", [this]() { exitGame(); } });
}

void GameUI::clearScreen() const {
    system(CLEAR_COMMAND);  // Clears the screen
}

void GameUI::run() {
    bool introDisplayed = false; // State variable to track if intro has been displayed

    while (true) {
        clearScreen();  // Clear the screen each time before showing the menu

        // Display the scrolling text only once
        if (!introDisplayed) {
            displayScrollingText("assets/intro.txt", 20);
            introDisplayed = true; // Set to true after displaying
        }

        displayMenu(); // Show the menu after intro text

        // Navigation using arrow keys
        char input = _getch(); // Use _getch() instead of getch()
        if (input == UP_ARROW) {
            selectedOption = (selectedOption - 1 + options.size()) % options.size(); // Wrap around
        }
        else if (input == DOWN_ARROW) {
            selectedOption = (selectedOption + 1) % options.size(); // Wrap around
        }
        else if (input == ENTER_KEY) {
            executeSelectedOption(); // Execute the action for the selected option
        }
    }
}

void GameUI::executeSelectedOption()
{
    options[selectedOption].action(); // Call the action for the selected option
}

void GameUI::displayMenu() {
    int rows, cols;
    getConsoleSize(rows, cols);  // Retrieve console size
    clearScreen();

    // Move cursor to the starting row for the menu
    int menuStartRow = (rows / 2) - (options.size() / 2); // Center menu vertically

    // Add empty lines for vertical centering
    for (int i = 0; i < menuStartRow; ++i) {
        std::cout << std::endl;
    }

    for (int i = 0; i < options.size(); ++i) {
        // Use the centerText function to display the options
        std::string optionText = (i == selectedOption)
            ? "> " + options[i].name + " <" // Highlight selected option
            : "  " + options[i].name + "  "; // Regular display

        centerText(optionText, cols); // Center the text for each menu option
    }
}

void GameUI::showCredits()
{
    std::string creditFile = "assets/credits.txt";
    displayScrollingText(creditFile, 20); 
}


void GameUI::displayScrollingText(const std::string& filename, int delayMs) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    int rows, cols;
    getConsoleSize(rows, cols);  // For centering
    clearScreen();  // Clear screen before showing text

    std::string line;
    while (std::getline(file, line)) {
        centerText(line, cols); // Use the helper function to center the line
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs)); // Delay for the specified time
    }

    file.close();
    std::cout << std::endl; // Add a line break before the prompt
    centerText("Press any key to continue...", cols); // Center the final message
    _getch(); // Wait for user input
}

void GameUI::centerText(const std::string& text, int consoleWidth) {
    int padding = (consoleWidth - static_cast<int>(text.size())) / 2; // Calculate padding for centering
    if (padding > 0) {
        std::cout << std::string(padding, ' '); // Print padding spaces
    }
    std::cout << text << std::endl; // Print the centered text
}

void GameUI::startNewGame() {
        std::vector<std::string> gameFiles;

        // Gather all .dll files from the games directory
        for (const auto& entry : std::filesystem::directory_iterator("./games")) {
            if (entry.path().extension() == ".dll") {
                gameFiles.push_back(entry.path().string()); // Store full paths
            }
        }

        if (gameFiles.empty()) {
            std::cout << "No games found in the games folder!\n";
            _getch();
            return;
        }

        int selectedGame = 0;
        while (true) 
        {
            clearScreen(); // Clear the screen
            std::cout << "Select a game:\n";

            // Display game options
            for (int i = 0; i < gameFiles.size(); ++i) {
                std::cout << (i == selectedGame ? "> " : "  ") << std::filesystem::path(gameFiles[i]).filename().string() << "\n";
            }

            char input = _getch();
            if (input == 72) { // Up arrow key
                selectedGame = (selectedGame - 1 + gameFiles.size()) % gameFiles.size();
            }
            else if (input == 80) { // Down arrow key
                selectedGame = (selectedGame + 1) % gameFiles.size();
            }
            else if (input == '\r') { // Enter key
                loadAndRunGame(gameFiles[selectedGame]); // Load the selected game
                break; // Exit loop after loading game
            }
        }
}

void GameUI::loadAndRunGame(const std::string & gamePath) {
    // Convert std::string to std::wstring
    std::wstring wideGamePath = std::wstring(gamePath.begin(), gamePath.end());

    HMODULE gameLib = LoadLibraryW(wideGamePath.c_str());

    if (!gameLib) {
        std::cerr << "Failed to load game: " << gamePath << std::endl;
        _getch();
        return; // Handle error appropriately
    }

    typedef Game* (*CreateGameFunc)();
    CreateGameFunc createGame = reinterpret_cast<CreateGameFunc>(
        GetProcAddress(gameLib, "createGame"));

    if (!createGame) {
        std::cerr << "Invalid game library: " << gamePath << std::endl;
        _getch();
        FreeLibrary(gameLib);
        return; // Handle error appropriately
    }

    Game* game = createGame(); // Create the game instance
    game->run();  // Run the game

    delete game; // Clean up the game object
    FreeLibrary(gameLib); // Free the library
}


void GameUI::loadGame() {

}





void GameUI::exitGame() {
    std::cout << "Exiting...\n";
    exit(0); // Exit the program
}

void GameUI::getConsoleSize(int& rows, int& cols)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        cols = csbi.srWindow.Right - csbi.srWindow.Left + 1; // Calculate number of columns
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1; // Calculate number of rows
    }
    else {
        // Fallback to default size in case of error
        cols = 80; // Default number of columns
        rows = 24; // Default number of rows
    }
}
