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
    size_t _points;
    size_t level;
    sf::Text text;
    sf::Font font;

    void initText();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    explicit Score()
        :_points(), level(), text(), font(){
        initText();
    }

    explicit Score(size_t startPoints)
            : _points(startPoints), level(), text(), font(){
        initText();
    }

    size_t getLevel() const{ return level; }

    // Setters
    void setLevel(size_t level);
    void add(size_t points);

    // Getters
    size_t getPoints();
};


#endif //TETRIS_SCORE_H
