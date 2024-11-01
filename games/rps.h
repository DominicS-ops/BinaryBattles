#ifndef RPSGAME_H
#define RPSGAME_H

#include "Game.h"
#include <iostream>
#include <string>
#include <cstdlib>  
#include <ctime>  


class RPSGame : public Game {
public:
    void run() override;

private:
    void displayMenu();
    void startGame();
    void displayHelp();
};

#endif  // RPSGAME_H
