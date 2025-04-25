#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#define GRAY sf::Color(57, 63, 78, 255)                      // board windows and sub-windows
#define LIGHT_BLUE sf::Color(82, 195, 225, 255)              // I piece
#define YELLOW sf::Color(226, 241, 97, 255)                  // O piece
#define ORANGE sf::Color(236, 169, 54, 255)                  // L piece
#define DARK_BLUE sf::Color(32, 85, 225, 255)                // J piece
#define RED sf::Color(225, 38, 38, 255)                      // Z piece
#define GREEN sf::Color(33, 172, 42, 255)                    // S piece
#define PURPLE sf::Color(104, 61, 212, 255)                  // T piece

int main()
{
    // render the main window 
    sf::RenderWindow window(sf::VideoMode({525, 675}), "Tetris by Daniel ;3");

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

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        
        window.clear();
        window.draw(*board);
        window.draw(*nextpiece);
        window.draw(*next3pieces);

        window.display();
    }

    /*
    sf::Clock mainClock;
    mainClock.start(); 

    std::string answer; 
    std::cout << "Answer: "; 
    std::cin >> answer; 
    while(answer != "stop") {
        std::cout << "No!!! Answer: ";
        std::cin >> answer; 
    }

    window.close();
    sf::Time elapsed = mainClock.getElapsedTime(); 
    mainClock.stop();
    std::cout << elapsed.asSeconds() << std::endl; 
    */
}