#include <iostream>
#include <string>
#include <vector>
#include <queue>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/OpenGL.hpp>

#include "game.hpp"
#include "piece.hpp"
#include "cell.hpp"

// updates all game data before rendering it to screen 
void updateGame() {

}

// handles all game events such as keypresses and mouseclicks
void handleEvents() {

}

int main()
{
    auto objs = new std::vector<std::unique_ptr<sf::Drawable>>();  

    // render the main window 
    sf::RenderWindow window(sf::VideoMode({525, 675}), "Tetris by Daniel ;3");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    // creating boards and objects where gameplay will happen
    auto board = std::make_unique<sf::RectangleShape>(sf::Vector2f(300, 575)); 
    board->setFillColor(GRAY);
    board->setPosition({30, 75});

    auto nextPiece = std::make_unique<sf::RectangleShape>(sf::Vector2f(150, 150));
    nextPiece->setFillColor(GRAY);
    nextPiece->setPosition({350, 75});

    auto next3Pieces = std::make_unique<sf::RectangleShape>(sf::Vector2f(100, 300));
    next3Pieces->setFillColor(GRAY);
    next3Pieces->setPosition({375, 240});

    auto holdPiece = std::make_unique<sf::RectangleShape>(sf::Vector2f(100, 100));
    holdPiece->setFillColor(GRAY);
    holdPiece->setPosition({375, 550});

    auto pauseButton = std::make_unique<sf::RectangleShape>(sf::Vector2f(50, 30));
    pauseButton->setFillColor(LIGHT_GRAY); 
    pauseButton->setPosition({30, 25});

    // text that will represent the score 
    sf::Font arial; 
    if (!arial.openFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
        std::cerr << "Error: can't load font file" << std::endl;
    }
    auto score = std::make_unique<sf::Text>(arial);
    score->setString("Score: ");
    score->setCharacterSize(20); 
    score->setPosition({200, 30});    
    score->setFillColor(sf::Color::White);
    score->setStyle(sf::Text::Bold);

    objs->push_back(std::move(board)); 
    objs->push_back(std::move(nextPiece)); 
    objs->push_back(std::move(next3Pieces)); 
    objs->push_back(std::move(holdPiece)); 
    objs->push_back(std::move(pauseButton)); 
    objs->push_back(std::move(score));



    // main application loop 
    while (window.isOpen()) { 
        // handles all game events
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) window.close(); 

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && 
            sf::Mouse::getPosition(window) == /*FIX*/ sf::Mouse::getPosition(window)){
                
            }
        }
        

        window.clear();
        for (const auto& o : *objs) {
            window.draw(*o);
        }
        window.display();
    }
}