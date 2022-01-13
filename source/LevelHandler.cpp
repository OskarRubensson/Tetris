// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// LevelHandler.cpp, 2022-01-10 - 2022-01-10
// kortfattat vad filen innehåller
//

#include "LevelHandler.h"

/**
 * Increases the level by a certain amount. However, the level never exceeds MAXLEVEL.
 * @param value Amount of levels to increase. Defaults to 1.
 */
void LevelHandler::increase(int value){
    if (value + currentLevel <= MAXLEVEL)
        currentLevel += value;
}

/**
 * Increases a ticker that when it reaches ticksPerLevel, a level-up is made.
 * @return Boolean depending on if a level-up was performed or not.
 */
bool LevelHandler::tick() {
    levelTicker++;
    if (levelTicker % ticksPerLevel != 0)
        return false;

    increase();
    return true;
}
