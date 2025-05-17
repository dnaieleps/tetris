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
    const sf::Vector2u screenSize(550, 700); 
    const sf::Vector2f blockSize(30, 30); 
    const sf::Vector2f boardSize(300, 600); 


    /****** CREATING ALL STATIC GAME OBJECTS ******/
    // render the main window 
    sf::RenderWindow window(sf::VideoMode(screenSize), "Tetris by Daniel ;3");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    // creating boards and objects where gameplay will happen
    auto board = std::make_unique<sf::RectangleShape>(boardSize); 
    board->setFillColor(GRAY);
    board->setPosition({30, 75});

    auto nextPiece = std::make_unique<sf::RectangleShape>(sf::Vector2f(150, 150));
    nextPiece->setFillColor(GRAY);
    nextPiece->setPosition({375, 75});

    auto next3Pieces = std::make_unique<sf::RectangleShape>(sf::Vector2f(100, 300));
    next3Pieces->setFillColor(GRAY);
    next3Pieces->setPosition({400, 240});

    auto holdPiece = std::make_unique<sf::RectangleShape>(sf::Vector2f(100, 100));
    holdPiece->setFillColor(GRAY);
    holdPiece->setPosition({400, 550});

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
    restartText->setPosition({35, 30});
    restartText->setFillColor(sf::Color::Black);

    // text for pause button 
    auto pauseText = std::make_unique<sf::Text>(arial);
    pauseText->setString("pause");
    pauseText->setCharacterSize(13);
    pauseText->setPosition({100, 30});
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
    
    /***** END OF CREATING GAME OBJECTS *****/



    // initializing game 
    Game* game = new Game();

    // main application loop 
    while (window.isOpen()) {

        // handles all game events and game updates 
        while (const std::optional event = window.pollEvent()) {
            // updates that occur regardless of user input (gameloop)


            
            // updates that happen only when prompted by user input (events)
            if(event.has_value()) {
                if (event->is<sf::Event::Closed>()) window.close();


                /*** ALL MOUSE CLICK EVENTS (FOR ONSCREEN BUTTONS) ***/
                if (event->is<sf::Event::MouseButtonPressed>() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    auto mousePos = sf::Mouse::getPosition(window); 
                    auto mousePosVec = sf::Vector2f({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)}); 

                    if (pauseButton->getGlobalBounds().contains(mousePosVec)) {
                        if (pauseIconHolder->getColor() == sf::Color(255, 255, 255, 128)) { // if pause is already activated
                            game->changePause();
                            pauseIconHolder->setColor(sf::Color(255, 255, 255, 0)); 
                        } else { 
                            pauseIconHolder->setColor(sf::Color(255, 255, 255, 128)); 
                        }
                    } else if (restartButton->getGlobalBounds().contains(mousePosVec)) {
                        window.close(); 
                        main(); 
                    }

                }


                /*** ALL KEYPRESS EVENTS ***/
                if (event->is<sf::Event::KeyPressed>()) {
                    auto keyPressed = event->getIf<sf::Event::KeyPressed>(); 
                    switch (keyPressed->scancode) {
                        case sf::Keyboard::Scancode::Escape: // close window
                            window.close(); 
                            break;
                        case sf::Keyboard::Scancode::P: // pause
                            if (pauseIconHolder->getColor() == sf::Color(255, 255, 255, 128)) { // if pause is already activated
                                game->changePause();
                                pauseIconHolder->setColor(sf::Color(255, 255, 255, 0)); 
                            } else { 
                                pauseIconHolder->setColor(sf::Color(255, 255, 255, 128)); 
                            }
                            break;
                        case sf::Keyboard::Scancode::R: // restart game
                            window.close(); 
                            main(); 
                            break;
                        case sf::Keyboard::Scancode::W: // rotate cw
                        case sf::Keyboard::Scancode::A: // move left
                        case sf::Keyboard::Scancode::S: // soft drop
                        case sf::Keyboard::Scancode::D: // move right 
                        case sf::Keyboard::Scancode::LShift: // hold 
                        case sf::Keyboard::Scancode::Up: // rotate cw
                        case sf::Keyboard::Scancode::Left: // move left
                        case sf::Keyboard::Scancode::Down: // soft drop
                        case sf::Keyboard::Scancode::Right: // move right
                        case sf::Keyboard::Scancode::RShift: // hold 
                        case sf::Keyboard::Scancode::Space: // hard drop
                         
                        default: 
                            std::cout << "no command exists for this key yet!" << std::endl; 
                            break;
                    }
                }
            }
        }
 
        for (int i = 0; i < (screenSize.x / blockSize.x); i++) { 
            for(int j = 0; j < (screenSize.y / blockSize.y); j++) {
                
            }
        }

        window.clear();  

        window.draw(*board); 
        window.draw(*nextPiece); 
        window.draw(*next3Pieces); 
        window.draw(*holdPiece); 
        window.draw(*restartButton); 
        window.draw(*pauseButton); 
        window.draw(*restartText); 
        window.draw(*pauseText); 
        window.draw(*score); 
        window.draw(*pauseIconHolder); 

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 20; j++) {
                sf::VertexArray tile(sf::PrimitiveType::LineStrip, 5); 
                // the position of the board's top left corner is at 30x75, and so that's where the tiles will originate
                // the dimensions of the board are 300x600, and each tile is supposed to be 30x30
                tile[0].position = sf::Vector2f((30 + (i * 30)), (75 + (j * 30))); 
                tile[1].position = sf::Vector2f((60 + (i * 30)), (75 + (j * 30))); 
                tile[2].position = sf::Vector2f((60 + (i * 30)), (105 + (j * 30))); 
                tile[3].position = sf::Vector2f((30 + (i * 30)), (105 + (j * 30))); 
                tile[4].position = sf::Vector2f((30 + (i * 30)), (75 + (j * 30))); 

                tile[0].color = sf::Color::White; 
                tile[1].color = sf::Color::White; 
                tile[2].color = sf::Color::White; 
                tile[3].color = sf::Color::White; 
                tile[4].color = sf::Color::White; 

                window.draw(tile); 
            }
        }

        /*
        sf::VertexArray triangle(sf::PrimitiveType::LineStrip, 3); 
        triangle[0].position = sf::Vector2f(10, 10); 
        triangle[1].position = sf::Vector2f(100, 10);
        triangle[2].position = sf::Vector2f(100, 100);
        
        triangle[0].color = sf::Color::White; 
        triangle[1].color = sf::Color::White; 
        triangle[2].color = sf::Color::White; 
        
        window.draw(triangle);
        */

        window.display(); 
    }

    delete game; 
    delete textures; 
}