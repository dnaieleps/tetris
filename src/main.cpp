#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>
#include <queue>

#include "game.hpp"
#include "piece.hpp"


int main()
{
    // render the main window 
    sf::RenderWindow window(sf::VideoMode({525, 675}), "Tetris by Daniel ;3");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    // creating boards where gameplay will happen
    sf::RectangleShape* board = new sf::RectangleShape({300, 575});
    board->setFillColor(GRAY);
    board->setPosition({30, 75});

    sf::RectangleShape* nextpiece = new sf::RectangleShape({150, 150});
    nextpiece->setFillColor(GRAY);
    nextpiece->setPosition({350, 75});

    sf::RectangleShape* next3pieces = new sf::RectangleShape({100, 300});
    next3pieces->setFillColor(GRAY);
    next3pieces->setPosition({375, 250});

    // pause button 
    sf::RectangleShape* pauseButton = new sf::RectangleShape({50, 30});
    pauseButton->setFillColor(LIGHT_GRAY); 
    pauseButton->setPosition({30, 25});

    /*
    sf::Font arial("arial.ttf");
    sf::Text* score = new sf::Text(arial, "Score: ", 25);
    score->setString("Score: ");
    score->setPosition({260, 25});
    */

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) window.close(); 
        }
        
        window.clear();

        window.draw(*board);
        window.draw(*nextpiece);
        window.draw(*next3pieces);
        window.draw(*pauseButton);
       // window.draw(*score);

        window.display();
    }

    delete board; 
    delete nextpiece;
    delete next3pieces;
    delete pauseButton;

}