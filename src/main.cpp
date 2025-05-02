#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>
#include <queue>

#include "game.hpp"
#include "piece.hpp"
#include "cell.hpp"


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

    sf::RectangleShape* nextPiece = new sf::RectangleShape({150, 150});
    nextPiece->setFillColor(GRAY);
    nextPiece->setPosition({350, 75});

    sf::RectangleShape* next3Pieces = new sf::RectangleShape({100, 300});
    next3Pieces->setFillColor(GRAY);
    next3Pieces->setPosition({375, 240});

    sf::RectangleShape* holdPiece = new sf::RectangleShape({100, 100});
    holdPiece->setFillColor(GRAY);
    holdPiece->setPosition({375, 550});

    // pause button 
    sf::RectangleShape* pauseButton = new sf::RectangleShape({50, 30});
    pauseButton->setFillColor(LIGHT_GRAY); 
    pauseButton->setPosition({30, 25});

    // score text
    sf::Font font; 
    if (!font.openFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
        std::cerr << "Error: can't load font file" << std::endl;
    }
    sf::Text score(font, "Score: ", 20);
    score.setPosition({200, 30});    
    score.setFillColor(sf::Color::White);
    score.setStyle(sf::Text::Bold);

    
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) window.close(); 
        }
        
        window.clear();

        window.draw(*board);
        window.draw(*nextPiece);
        window.draw(*next3Pieces);
        window.draw(*pauseButton);
        window.draw(*holdPiece);
        window.draw(score);

        window.display();
    }

    delete board; 
    delete nextPiece;
    delete next3Pieces;
    delete pauseButton;
    delete holdPiece; 
}