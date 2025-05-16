#pragma once 
#include <SFML/Graphics.hpp>

class Cell {
private: 
    sf::RectangleShape cell; 
    bool filled; 
public: 
    Cell(); 
    ~Cell(); 
    bool getFilled(); 
    bool changeFilled(); 
};