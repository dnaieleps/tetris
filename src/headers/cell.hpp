#pragma once 
#include <SFML/Graphics.hpp>

class Cell {
private:
    sf::RectangleShape cover;
    bool filled; 
public: 
    const static sf::Vector2f cellDimensions; 
    const static sf::Vector2f miniCellDimensions; 
    Cell() = default; 
    Cell(sf::RectangleShape& cover_);
    ~Cell() = default; 
    bool isFilled(); 
    bool changeFilled(); 
    
    sf::RectangleShape& getCover(); 
    sf::RectangleShape& setCover(sf::RectangleShape& newcover); 
};