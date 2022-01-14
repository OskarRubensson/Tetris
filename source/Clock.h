// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Clock.h, 2021-12-20 - 2022-01-13
// Contains the declaration of the Clock-class.
//

#ifndef TETRIS_CLOCK_H
#define TETRIS_CLOCK_H


#include <ctime>
#include <chrono>

/**
 * A clock that can be used when something should be done in an interval.
 */
class Clock {
    size_t clockrate;
    bool running;
    std::chrono::time_point<std::chrono::steady_clock> last_clock;

public:
    const static int DEFAULT_CLOCKRATE = 1000;

    /**
     * Default constructor - Uses parametrized constructor with Clock::DEFAULT_CLOCKRATE.
     */
    Clock(): Clock(DEFAULT_CLOCKRATE) {}
    explicit Clock(size_t clockrate);

    bool hasTicked();
    void stop();
    void start(bool reset = false);

    /**
     * Check-function to see if clock is running or not.
     * @return bool based on if clock is running.
     */
    [[nodiscard]] bool isRunning() const { return running; }
    [[nodiscard]] size_t getClockrate() const;
    void setClockrate(int newClockrate);

};


#endif //TETRIS_CLOCK_H
