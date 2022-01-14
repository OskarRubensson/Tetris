// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Clock.cpp, 2021-12-20 - 2022-01-13
// Contains the implementations of the Clock-class' functions.
//

#include "Clock.h"
#include <iostream>
#include <chrono>

/**
 * Parametrized constructor. Creates a clock with a given clockrate
 * @param clockrate The clockrate to set the clock to.
 */
Clock::Clock(size_t clockrate):
    last_clock(std::chrono::high_resolution_clock::now()),
    clockrate(clockrate),
    running(false){
}

/**
 * Check-function to see if a clockrate-time has passed.
 * @return True if clock is running and a clockrate has passed since this was last run.
 */
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

/**
 * Stops the clock.
 */
void Clock::stop() {
    running = false;
}

/**
 * Starts the clock.
 * @param reset if true then clock restarts. Otherwise, it resumes. Defaults to false
 */
void Clock::start(bool reset) {
    if (reset)
        last_clock = std::chrono::high_resolution_clock::now();
    running = true;
}

/**
 * Getter for clockrate.
 * @return clockrate.
 */
size_t Clock::getClockrate() const {
    return clockrate;
}

/**
 * Setter for clockrate.
 * @param newClockrate The new clockrate to be used.
 */
void Clock::setClockrate(int newClockrate) {
    if (newClockrate >= 20)
        clockrate = newClockrate;
}