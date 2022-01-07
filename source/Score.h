// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Score.h, 2022-01-07 - 2022-01-07
// kortfattat vad filen innehåller
//

#ifndef TETRIS_SCORE_H
#define TETRIS_SCORE_H


#include <cstddef>

class Score {
    size_t _points = 0;
    size_t level = 1;

public:

    Score() = default;
    explicit Score(size_t startPoints)
        : _points(startPoints)
    {}

    // Setters
    void setLevel(size_t level);
    void add(size_t points);

    // Getters
    size_t getPoints();
};


#endif //TETRIS_SCORE_H
