// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Menu.h, 2022-01-10 - 2022-01-10
// kortfattat vad filen innehåller
//

#ifndef TETRIS_MENU_H
#define TETRIS_MENU_H


#include <SFML/Graphics/Drawable.hpp>
#include <utility>
#include "Button.h"

/**
 * A container for buttons that are stacked vertically with a given spacing between them.
 */
class Menu: public sf::Transformable, public sf::Drawable {
    std::vector<std::unique_ptr<Button>> buttons;
    std::vector<std::unique_ptr<Button>>::iterator hoveredBtn;
    sf::RectangleShape hoverShape;
    sf::RectangleShape fadedBackground;
    const int spacing;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    /**
     * \public Numerical value representing moving upwards in the menu.
     */
    static const int UP = 1;

    /**
     * \public Numerical value representing moving downwards in the menu.
     */
    static const int DOWN = -1;

    explicit Menu(std::vector<std::string> buttonStrings, int spacing = 30);

    /**
     * To simulate a click. But instead of taking in callback-function it gives you the ID of the clicked button.
     * @return Index of the clicked btn.
     */
    size_t click() { return std::distance(buttons.begin(), hoveredBtn); }
    void move(int direction);
};


#endif //TETRIS_MENU_H
