// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Score.cpp, 2022-01-07 - 2022-01-07
// kortfattat vad filen innehåller
//

#include "Score.h"

void Score::setLevel(size_t level) {
    this->level = level;
}

size_t Score::getPoints() {
    return _points;
}

void Score::add(size_t points) {
    switch(points){
        case 4:
            _points += 1000 * (level + 1);
            break;
        case 3:
            _points += 350 * (level + 1);
            break;
        case 2:
            _points += 150 * (level + 1);
            break;
        default:
            _points += 50 * (level + 1);
            break;
    }
}
