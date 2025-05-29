#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <memory>
#include <random>

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
    sf::RectangleShape board(boardSize); 
    board.setFillColor(GRAY);
    board.setPosition({30, 75});

    sf::RectangleShape nextPiece(sf::Vector2f(150, 150));
    nextPiece.setFillColor(GRAY);
    nextPiece.setPosition({375, 75});

    sf::RectangleShape next3Pieces(sf::Vector2f(100, 300));
    next3Pieces.setFillColor(GRAY);
    next3Pieces.setPosition({400, 240});

    sf::RectangleShape holdPiece(sf::Vector2f(100, 100));
    holdPiece.setFillColor(GRAY);
    holdPiece.setPosition({400, 550});

    sf::RectangleShape restartButton(sf::Vector2f(50, 30)); 
    restartButton.setFillColor(LIGHT_GRAY);
    restartButton.setPosition({30, 25}); 

    sf::RectangleShape pauseButton(sf::Vector2f(50, 30));
    pauseButton.setFillColor(LIGHT_GRAY); 
    pauseButton.setPosition({95, 25});

    // universal font to be used for all text in game
    sf::Font arial; 
    if (!arial.openFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
        std::cerr << "Error: can't load font file" << std::endl;
    }

     // text for restart button 
    sf::Text restartText(arial); 
    restartText.setString("restart");
    restartText.setCharacterSize(13);
    restartText.setPosition({35, 30});
    restartText.setFillColor(sf::Color::Black);

    // text for pause button 
    sf::Text pauseText(arial); 
    pauseText.setString("pause");
    pauseText.setCharacterSize(13);
    pauseText.setPosition({100, 30});
    pauseText.setFillColor(sf::Color::Black);

    // text that will represent the score 
    sf::Text score(arial); 
    score.setString("Score: ");
    score.setCharacterSize(20); 
    score.setPosition({200, 30});    
    score.setFillColor(sf::Color::White);
    score.setStyle(sf::Text::Bold);

    // loading in pause icon texture from file
    auto textures = new std::vector<sf::Texture*>();
    auto pauseTexture = new sf::Texture(); 
    if(!pauseTexture->loadFromFile("../resources/pause.png")) {
        std::cerr << "Error: could not load image from file" << std::endl; 
    }

    // creating sprite where pauseTexture will be placed
    sf::Sprite pauseIconHolder(*pauseTexture); 
    pauseIconHolder.setPosition({(525 - 200) / 2, (675 - 200) / 2});
    pauseIconHolder.setScale({0.4, 0.4}); 
    pauseIconHolder.setColor(sf::Color(255, 255, 255, 0)); 
    textures->push_back(pauseTexture);
    
    /***** END OF CREATING GAME OBJECTS *****/

    // initializing the game instance 
    Game* game = new Game();
    
   /*** START OF GAME APPLICATION LOOP ***/
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

                    if (pauseButton.getGlobalBounds().contains(mousePosVec)) {
                        if (pauseIconHolder.getColor() == sf::Color(255, 255, 255, 128)) { // if pause is already activated
                            game->changePause();
                            pauseIconHolder.setColor(sf::Color(255, 255, 255, 0)); 
                        } else { 
                            pauseIconHolder.setColor(sf::Color(255, 255, 255, 128)); 
                        }
                    } else if (restartButton.getGlobalBounds().contains(mousePosVec)) {
                        window.close(); 
                        main(); 
                    }

                }
                /*** END OF MOUSE CLICK EVENT HANDLING ***/


                /*** ALL KEYPRESS EVENTS ***/
                if (event->is<sf::Event::KeyPressed>()) {
                    auto keyPressed = event->getIf<sf::Event::KeyPressed>(); 
                    
                    switch (keyPressed->scancode) {
                        case sf::Keyboard::Scancode::Escape: // close window
                            window.close(); 
                            break;
                        case sf::Keyboard::Scancode::Tab: // pause
                            if (pauseIconHolder.getColor() == sf::Color(255, 255, 255, 128)) { // if pause is already activated
                                game->changePause();
                                pauseIconHolder.setColor(sf::Color(255, 255, 255, 0)); 
                            } else { 
                                pauseIconHolder.setColor(sf::Color(255, 255, 255, 128)); 
                            }
                            break;
                        case sf::Keyboard::Scancode::R: // restart game
                            window.close(); 
                            main(); 
                            break;
                        case sf::Keyboard::Scancode::W: // rotate cw
                            break;
                        case sf::Keyboard::Scancode::A: // move left
                            break;
                        case sf::Keyboard::Scancode::S: // soft drop
                            break;
                        case sf::Keyboard::Scancode::D: // move right 
                            break;
                        case sf::Keyboard::Scancode::LShift: // hold 
                            break;
                        case sf::Keyboard::Scancode::Up: // rotate cw
                            break;
                        case sf::Keyboard::Scancode::Left: // move left
                            break;
                        case sf::Keyboard::Scancode::Down: // soft drop
                            break;
                        case sf::Keyboard::Scancode::Right: // move right
                            break;
                        case sf::Keyboard::Scancode::RShift: // hold 
                            break;
                        case sf::Keyboard::Scancode::Space: // hard drop
                            break;


                        /*** DEBUGGING COMMANDS ***/
                        case sf::Keyboard::Scancode::I: // debugging
                            std::cout << "contents of queue: "; 
                            if (game->pieceQueue.empty()) {
                                std::cout << "nothing! it is empty" << std::endl; 
                            } else { 
                                // making temporary copy of the game's pieceQueue cus i wanna keep the actual values of the queue
                                std::queue<Piece*> tempQueue = game->pieceQueue; 
                                while (!tempQueue.empty()) {
                                    std::cout << tempQueue.front()->getType() << ", "; 
                                    tempQueue.pop(); 
                                }
                            }
                            std::cout << std::endl; 
                            break; 
                        case sf::Keyboard::Scancode::O: // debugging
                            game->spawnPiece(*(game->pieceQueue.front())); 
                            game->pieceQueue.pop(); 
                            break; 
                        case sf::Keyboard::Scancode::P: // debugging
                            std::cout << "adding value to top of queue"; 
                            game->addRandomPieceToQueue(); 
                            std::cout << std::endl; 
                            break; 
                        /*** END OF DEBUGGING COMMANDS ***/

                        
                        default: 
                            std::cout << "no command exists for this key yet!" << std::endl; 
                            break;
                    }
                }
                /*** END OF KEYPRESS EVENT HANDLING ***/
            }
        }

        

        /*** DRAWING EVERYTHING TO SCREEN ***/
        window.clear();  

        window.draw(board); 
        window.draw(nextPiece); 
        window.draw(next3Pieces); 
        window.draw(holdPiece); 
        window.draw(restartButton); 
        window.draw(pauseButton); 
        window.draw(restartText); 
        window.draw(pauseText); 
        window.draw(score); 
        window.draw(pauseIconHolder); 

        // building the grid where the blocks will all be placed
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

                tile[0].color = tile[1].color = tile[2].color = tile[3].color = tile[4].color = sf::Color(343540);
                window.draw(tile); 
            }
        }

        // drawing all the tiles from the cell grid onto the screen
        for (std::array<Cell*, 10> &row : game->grid) {
            for (Cell* t : row) {
                window.draw(t->getCover()); 
            }
        }

        window.display(); 
        /*** END OF DRAWING TO SCREEN ***/
    }
    /*** END OF GAME APPLICATION LOOP ***/

    delete game; 
    delete textures; 
}