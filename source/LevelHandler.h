// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// LevelHandler.h, 2022-01-10 - 2022-01-13
// Contains the declaration of the LevelHandler-class.
//

#ifndef TETRIS_LEVELHANDLER_H
#define TETRIS_LEVELHANDLER_H


#include <cstddef>

/**
 * A handler for tetris-like levels. The level is increased when a ticker has reached a certain value.
 */
class LevelHandler {
    const static size_t MAXLEVEL = 20;
    const size_t ticksPerLevel = 15;
    size_t levelTicker = 0;
    size_t currentLevel = 0;

public:
    LevelHandler() = default;

    void increase(int value = 1);
    bool tick();
    /**
     * Getter for the current level
     * @return Numerical value of the current level.
     */
    [[nodiscard]] size_t getLevel() const { return currentLevel; }

};


#endif //TETRIS_LEVELHANDLER_H
