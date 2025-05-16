#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/OpenGL.hpp>

#include "headers/game.hpp"
#include "headers/piece.hpp"
#include "headers/cell.hpp"

int main()
{
    // initializing game 
    Game* game = new Game();

    /****** RENDERING ALL GAME OBJECTS ******/
    auto objs = new std::vector<std::unique_ptr<sf::Drawable>>();  

    // render the main window 
    sf::RenderWindow window(sf::VideoMode({525, 675}), "Tetris by Daniel ;3");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    // creating boards and objects where gameplay will happen
    auto board = std::make_unique<sf::RectangleShape>(sf::Vector2f(300, 575)); 
    board->setFillColor(GRAY);
    board->setPosition({30, 75});

    int gridRows = 20; 
    int gridCols = 10; 
    // auto grid = new sf::VectorArray(sf::Lines, 2 * (gridRows + gridCols - 2));      FIX THIS NOW. 



    auto nextPiece = std::make_unique<sf::RectangleShape>(sf::Vector2f(150, 150));
    nextPiece->setFillColor(GRAY);
    nextPiece->setPosition({350, 75});

    auto next3Pieces = std::make_unique<sf::RectangleShape>(sf::Vector2f(100, 300));
    next3Pieces->setFillColor(GRAY);
    next3Pieces->setPosition({375, 240});

    auto holdPiece = std::make_unique<sf::RectangleShape>(sf::Vector2f(100, 100));
    holdPiece->setFillColor(GRAY);
    holdPiece->setPosition({375, 550});

    auto restartButton = std::make_unique<sf::RectangleShape>(sf::Vector2f(50, 30)); 
    restartButton->setFillColor(LIGHT_GRAY);
    restartButton->setPosition({30, 25}); 

    auto pauseButton = std::make_unique<sf::RectangleShape>(sf::Vector2f(50, 30));
    pauseButton->setFillColor(LIGHT_GRAY); 
    pauseButton->setPosition({95, 25});

    // universal font to be used for all text in game
    sf::Font arial; 
    if (!arial.openFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
        std::cerr << "Error: can't load font file" << std::endl;
    }

     // text for restart button 
    auto restartText = std::make_unique<sf::Text>(arial);
    restartText->setString("restart");
    restartText->setCharacterSize(13);
    restartText->setPosition({100, 30});
    restartText->setFillColor(sf::Color::Black);

    // text for pause button 
    auto pauseText = std::make_unique<sf::Text>(arial);
    pauseText->setString("pause");
    pauseText->setCharacterSize(13);
    pauseText->setPosition({35, 30});
    pauseText->setFillColor(sf::Color::Black);

    // text that will represent the score 
    auto score = std::make_unique<sf::Text>(arial);
    score->setString("Score: ");
    score->setCharacterSize(20); 
    score->setPosition({200, 30});    
    score->setFillColor(sf::Color::White);
    score->setStyle(sf::Text::Bold);

    // loading in pause icon texture from file
    auto textures = new std::vector<std::unique_ptr<sf::Texture>>();
    auto pauseTexture = std::make_unique<sf::Texture>(); 
    if(!pauseTexture->loadFromFile("../resources/pause.png")) {
        std::cerr << "Error: could not load image from file" << std::endl; 
    }

    // creating sprite where pauseTexture will be placed
    auto pauseIconHolder = std::make_unique<sf::Sprite>(*pauseTexture);
    pauseIconHolder->setPosition({(525 - 200) / 2, (675 - 200) / 2});
    pauseIconHolder->setScale({0.4, 0.4}); 
    pauseIconHolder->setColor(sf::Color(255, 255, 255, 0)); 
    textures->push_back(std::move(pauseTexture));

    // adding all screen components to objs vector 
    objs->push_back(std::move(board)); 
    objs->push_back(std::move(nextPiece)); 
    objs->push_back(std::move(next3Pieces)); 
    objs->push_back(std::move(holdPiece)); 
    objs->push_back(std::move(restartButton));
    objs->push_back(std::move(pauseButton)); 
    objs->push_back(std::move(restartText));
    objs->push_back(std::move(pauseText));
    objs->push_back(std::move(score));
    objs->push_back(std::move(pauseIconHolder));
    /***** END OF RENDERING *****/




    // main application loop 
    while (window.isOpen()) {

        // handles all game events and game updates 
        while (const std::optional event = window.pollEvent()) {
            // updates that occur regardless of user input (gameloop)


            
            // updates that happen only when prompted by user input (events)
            if (event->is<sf::Event::Closed>()) window.close();
            
            if (event->is<sf::Event::KeyPressed>()) {
                auto keyPressed = event->getIf<sf::Event::KeyPressed>(); 
                
                switch (keyPressed->scancode) {
                    case sf::Keyboard::Scancode::Escape: 
                        window.close(); 
                    case sf::Keyboard::Scancode::P: 
                        game->changePause(); 
                        pauseIconHolder->setColor(sf::Color(255, 255, 255, 128)); 
                    default: 
                        std::cout << "no command exists for this key yet!" << std::endl; 

                }
            }
            
            /* mouse events (to be implemented)
            if (event->is<sf::Event::MouseButtonPressed>()) { 
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    auto mousePos = sf::Mouse::getPosition(window); 
                    auto mousePosWindow = window.mapPixelToCoords(mousePos);

                    if (pauseButton->getGlobalBounds().contains(mousePosWindow)) {
                        pauseIconHolder->setColor(sf::Color(255, 255, 255, 128)); 
                    } 
                }
            }
                */
        }
        
        // redraws all components to screen every game loop as needed
        window.clear();
        for (const auto& o : *objs) {
            window.draw(*o);
        }
        window.display();
    }

    delete game; 
    delete objs; 
    delete textures; 
}