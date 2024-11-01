// game.h
#ifndef GAME_H
#define GAME_H

class Game {
public:
    virtual ~Game() = default;  // Ensure proper cleanup for derived classes
    virtual void run() = 0;      // All games must implement the run() function
};

#endif  // GAME_H
