// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Score.h, 2022-01-07 - 2022-01-07
// kortfattat vad filen innehåller
//

#ifndef TETRIS_SCORE_H
#define TETRIS_SCORE_H


#include <cstddef>
#include <SFML/Graphics.hpp>

class Score: public sf::Transformable, public sf::Drawable {
    size_t score;
    size_t level;
    sf::Text text;
    sf::Font font;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    explicit Score(size_t startScore = 0);

    // Getters
    [[nodiscard]] size_t getLevel() const{ return level; }
    [[nodiscard]] size_t getScore() const { return score; }

    // Setters
    /**
     * Increases the current level.
     * @param newLevel Amount of levels to increase with. Defaults to 1.
     */
    void increaseLevel(size_t newLevel = 1) { level += newLevel; };
    void add(size_t points);

};


#endif //TETRIS_SCORE_H
