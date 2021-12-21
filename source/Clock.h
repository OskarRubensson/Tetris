// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Clock.h, 2021-12-20 - 2021-12-20
// kortfattat vad filen innehåller
//

#ifndef TETRIS_CLOCK_H
#define TETRIS_CLOCK_H


#include <ctime>
#include <chrono>

class Clock {
    const int DEFAULT_CLOCKRATE = 1000;
    int clockrate;
    std::chrono::time_point<std::chrono::steady_clock> last_clock;

public:
    Clock();
    Clock(int clockrate);

    bool hasTicked();
};


#endif //TETRIS_CLOCK_H
