# BinaryBattles

## Overview
BinaryBattles is a C++ project that implements a collection of two-player games as dynamic link libraries (DLLs). This project focuses on modularity, maintainability, and a user-friendly interface.

## Prerequisites
- C++ Compiler (e.g., g++, MinGW)
- Git (for version control)

## Project Structure
```
/BinaryBattles
|-- /games
|   |-- Connect4game.dll
|   |-- simplegame.dll
|   |-- rps.dll
|-- /src
|   |-- main.cpp
|   |-- Menu.cpp
|   |-- (other source files)
|-- README.md
```

## Compiling the Project

### Compiling a DLL for a Game
To compile the Rock-Paper-Scissors (RPS) game as a DLL, use the following command:
```bash
g++ -shared -o rps.dll rps.cpp
```

### Compiling the Main Menu Application
To compile the main application that includes the menu, use:
```bash
g++ main.cpp Menu.cpp -o BinaryBattles
```

## Running the Games
1. Ensure the DLL files are in the correct directory.
2. Launch the main application:
   ```bash
   ./BinaryBattles
   ```
3. Follow the on-screen instructions to navigate the menu and play the games.

## Contributing
Feel free to submit pull requests or report issues. Contributions are welcome!

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
