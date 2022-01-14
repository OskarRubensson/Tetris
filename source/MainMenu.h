// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// MainMenu.h, 2022-01-13 - 2022-01-13
// Contains the declaration for the MainMenu class.
//

#ifndef TETRIS_MAINMENU_H
#define TETRIS_MAINMENU_H

#include <SFML/Graphics.hpp>
#include "Menu.h"

/**
 * Class that contains the tetris-logo, title and a menu.
 */
class MainMenu: public sf::Drawable, public sf::Transformable {
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    sf::Sprite logo;
    sf::Texture img;
    Menu menu;

    /**
     * Parametrized constructor. Creates a main menu with given logoPath on top and a menu with buttons according to buttonString below.
     * @param logoPath Path to the image-file of the logo.
     * @param buttonString A set of strings to create buttons from.
     */
    MainMenu(std::string logoPath, std::vector<std::string> buttonString)
    :menu(std::move(buttonString)), logo(){
        if (img.loadFromFile(logoPath))
            logo.setTexture(img, true);
        menu.setPosition(sf::Vector2<float>(0, logo.getGlobalBounds().height + 50));
    }

    /**
     * Getter for the main menus size.
     * @return sf::Vector2<float> containing the total size of the menu.
     */
    sf::Vector2<float> getSize(){
        return sf::Vector2<float>{
                (menu.getSize().x > logo.getGlobalBounds().width ? menu.getSize().x : logo.getGlobalBounds().width),
                menu.getSize().y + logo.getGlobalBounds().height
        };
    }
};


#endif //TETRIS_MAINMENU_H
