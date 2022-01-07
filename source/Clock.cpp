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
    running(false){
}


Clock::Clock(size_t clockrate):
    last_clock(std::chrono::high_resolution_clock::now()),
    DEFAULT_CLOCKRATE(clockrate),
    clockrate(clockrate),
    running(false){
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

void Clock::start(bool reset) {
    if (reset)
        last_clock = std::chrono::high_resolution_clock::now();
    running = true;
}

size_t Clock::getClockrate() {
    return clockrate;
}

void Clock::setClockrate(int newClockrate) {
    if (newClockrate >= 20)
        clockrate = newClockrate;
}