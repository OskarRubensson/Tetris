//
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900)
// Score.cpp, 2022-01-07 - 2022-01-07
// kortfattat vad filen innehåller
//

#include "Score.h"

/**
 * Default and Parametrized constructor. startScore defaults to 0.
 * @param startScore Score to start at. Defaults to 0.
 */
Score::Score(size_t startScore)
: score(startScore), level(), text(), font(){
    if (font.loadFromFile("../resources/fonts/Pacifico.ttf")){
        text.setFont(font);
        text.setString("Score: 0");
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
    }
}

/**
 * Draws "Score: X" at the set position and target.
 * @param target Target to draw on.
 * @param states States given from parent.
 */
void Score::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(text, states);
}

/**
 * Adds a certain amount of points. Points are translated to a score with the current level.
 * @param points Amount of points to add. It's multiplied by current level etc. Therefore, points is often a low value.
 */
void Score::add(size_t points) {
    switch(points){
        case 4:
            score += 1000 * (level + 1);
            break;
        case 3:
            score += 350 * (level + 1);
            break;
        case 2:
            score += 150 * (level + 1);
            break;
        default:
            score += 50 * (level + 1);
            break;
    }

    text.setString("Score: " + std::to_string(score));
}

