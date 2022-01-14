// 
// Tetris, Programmeringsmetodik (DT047G)
// Oskar Rubensson (osru1900) 
// Window.cpp, 2021-12-15 - 2022-01-13
// Contains the implementations of the Window-class' functions.
//

#include "Window.h"

/**
 * Parametrized constructor. Creates a window with a given width, height & title.
 * Also initializes all the game components, such as game, main menu etc.
 * @param width Width of the window to create.
 * @param height Height of the window to create.
 * @param title Title of the window to create.
 */
Window::Window(int width, int height, const std::string& title)
:renderWindow(sf::VideoMode(width, height),title),
game(std::make_unique<Game>()),
mainMenu(std::make_unique<MainMenu>(LOGO_PATH, std::vector<std::string>{"Start", "Quit"})),
currentState(MAIN_MENU){
    initialization();
}

/**
 * Initializes the position and size of each main-screens (game, main menu...)
 */
void Window::initialization() {
    renderWindow.setFramerateLimit(60);
    sf::Vector2<float> windowCenter = {
            (float)renderWindow.getSize().x / 2,
            (float)renderWindow.getSize().y / 2};
    mainMenu->setPosition(windowCenter - sf::Vector2<float>{mainMenu->getSize().x / 2, mainMenu->getSize().y});
    game->setScale({1.4f, 1.6f});
    game->setPosition(windowCenter - sf::Vector2<float>{game->width() / 2, game->height() / 2});
}

/**
 * Runs the window, and will keep it running until window is closed.
 * Also handles any events and starts the recursive "draw"-function of each element.
 */
void Window::run(){
    while(renderWindow.isOpen()){
        handleEvent();
        renderWindow.clear(BG_COLOR);

        // Draw correct object based on currentState
        switch (currentState){
            case GAME :
                // If game is in game-over state, reset it.
                if (game->getState() == Game::GAME_OVER) {
                    game.reset();
                    game = std::make_unique<Game>();
                    initialization();
                    currentState = MAIN_MENU;
                }
                game->update();
                renderWindow.draw(*game);
                break;
            case MAIN_MENU:
                renderWindow.draw(*mainMenu);
                break;
        }
        renderWindow.display();
    }
}

/**
 * Handle any event that is lying in the event-queue
 */
void Window::handleEvent() {
    sf::Event event{};
    while(renderWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            renderWindow.close();
        }
        // On user input -> handleInput
        if (event.type == sf::Event::KeyPressed ||
            event.type == sf::Event::KeyReleased){
            handleInput(event);
        }
    }
}

/**
 * Handles any user input. Redirects it to the game if its running, or menu it that is running.
 * @param event Event to handle
 */
void Window::handleInput(sf::Event& event){
    switch (currentState){
        case GAME:
            handleGameInput(event);
            break;
        case MAIN_MENU:
            handleMainMenuInput(event);
            break;

    }
}

/**
 * Handle each input that the game can handle.
 * @param event Event containing the input that was given
 */
void Window::handleGameInput(sf::Event& event) {
    // GAME RUNNING INPUT
    if (game->getState() == Game::RUNNING){
        auto moveFunc = [&](size_t dir){
            if (event.type == sf::Event::KeyPressed)
                game->startMove(dir);
            else if (event.type == sf::Event::KeyReleased)
                game->stopMove();
        };

        if (event.key.code == sf::Keyboard::Left) // LEFT
            moveFunc(Game::LEFT);
        if (event.key.code == sf::Keyboard::Right) // RIGHT
            moveFunc(Game::RIGHT);
        if (event.key.code == sf::Keyboard::Up) // UP
            moveFunc(Game::UP);
        if (event.key.code == sf::Keyboard::Down) // DOWN
            moveFunc(Game::DOWN);
        if (event.key.code == sf::Keyboard::Z && event.type == sf::Event::KeyReleased) // Z
            game->rotate(false);
        if (event.key.code == sf::Keyboard::X && event.type == sf::Event::KeyReleased) // X
            game->rotate(true);
        if (event.key.code == sf::Keyboard::Escape && event.type == sf::Event::KeyReleased) // X
            game->pause();

        // PAUSED INPUT
    } else if (game->getState() == Game::PAUSED && event.type == sf::Event::KeyReleased){
        if (event.key.code == sf::Keyboard::Up) // UP
            game->menuInput(Game::UP);
        if (event.key.code == sf::Keyboard::Down) // DOWN
            game->menuInput(Game::DOWN);
        if (event.key.code == sf::Keyboard::Enter) // ENTER
            game->menuInput(Game::ENTER);
    }
}

void Window::handleMainMenuInput(sf::Event& event) {
    // Only handle sf::Event::KeyReleased
    if (event.type == sf::Event::KeyPressed)
        return;

    if (event.key.code == sf::Keyboard::Up) // UP
        mainMenu->menu.move(Menu::UP);
    if (event.key.code == sf::Keyboard::Down) // DOWN
        mainMenu->menu.move(Menu::DOWN);
    if (event.key.code == sf::Keyboard::Enter){ // Enter
        size_t btnID = mainMenu->menu.click();
        if (btnID == 0)
            setState(GAME);
        else
            renderWindow.close();
    }
}

/**
 * Getter for the state of the window. If it is running the game, showing the main menu etc.
 * @return The windows state
 */
State Window::getState() const{
    return currentState;
}

/**
 * Sets the state of the window
 * @param newState New state to set.
 */
void Window::setState(State newState){
    currentState = newState;
}
