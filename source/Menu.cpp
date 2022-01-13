// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Menu.cpp, 2022-01-10 - 2022-01-10
// kortfattat vad filen innehåller
//

#include "Menu.h"
/**
 * Parametrized constructor for the menu. Creates a menu with buttons that has a given text.
 * @param buttonStrings A vector of strings for each button's text to represent.
 * @param spacing The spacing to have between the buttons. Defaults to 30.
 */
Menu::Menu(std::vector<std::string> buttonStrings, int spacing): spacing(spacing) {
    // Initialize all button values
    float maxWidth = 0;
    for(int i = 0; i < buttonStrings.size(); i++){
        buttons.emplace_back(std::make_unique<Button>(buttonStrings[i]));
        auto& b = buttons.back();
        b->setPosition(0, (float)i * ((float)spacing + b->getHeight()) - 5);

        if (b->getWidth() > maxWidth)
            maxWidth = b->getWidth();
    }

    // Initialize fadedBackground
    fadedBackground.setSize({100000, 100000});
    fadedBackground.setFillColor(sf::Color(0, 0, 0, 200));

    // Initialize hover-shape
    hoverShape.setFillColor(sf::Color::Cyan * sf::Color(255, 255, 255, 150));
    hoverShape.setSize({maxWidth + 10, buttons.front()->getHeight()});
    hoverShape.setOutlineThickness(5);
    hoverShape.setOutlineColor(hoverShape.getFillColor() * sf::Color(255, 255, 255, 150));

    // Start hovering top button
    hoveredBtn = buttons.begin();
}

/**
 * Draws the menu onto the target. More specifically, calls draw on each button the menu contains.
 * @param target Target to draw on.
 * @param states States given from the parent element.
 */
void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(fadedBackground); //Position in 0, 0 so that it covers the screen
    target.draw(hoverShape, states);
    for(auto& b: buttons) {
        target.draw(*b, states);
    }
}

/**
 * Moves which button is hovered in a circular manner. Also sets the position of the hover-shape.
 * @param direction Menu::UP or Menu::DOWN (1 or -1) will make a move.
 */
void Menu::move(int direction) {
    if (hoveredBtn + direction >= buttons.end()){
        hoveredBtn = buttons.begin();
    } else if (hoveredBtn + direction < buttons.begin()){
        hoveredBtn = buttons.end() - 1;
    } else
        hoveredBtn += direction;
    hoverShape.setPosition({0,
                            std::distance(buttons.begin(), hoveredBtn) * (buttons.front()->getHeight() + spacing)});
}
