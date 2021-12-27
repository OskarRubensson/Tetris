// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Clock.cpp, 2021-12-20 - 2021-12-20
// kortfattat vad filen innehåller
//

#include "Clock.h"
#include <iostream>
#include <chrono>

Clock::Clock():
    last_clock(std::chrono::high_resolution_clock::now()),
    clockrate(DEFAULT_CLOCKRATE),
    running(true){
}


Clock::Clock(int clockrate):
    last_clock(std::chrono::high_resolution_clock::now()),
    DEFAULT_CLOCKRATE(clockrate),
    clockrate(clockrate),
    running(true){
}

bool Clock::hasTicked(){
    if (!running)
        return false;

    auto now = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_clock);

    if (dur.count() >= clockrate){
        last_clock = now;
        return true;
    }
    return false;
}

void Clock::stop() {
    running = false;
}

void Clock::start() {
    running = true;
}