#pragma once 
#include <SFML/Graphics.hpp>

/* class definition that serves as the blueprint for each of the Tetris pieces
*   @cover -> sf::RectangleShape that just stores the visual part (color) of the cell 
*   @active -> determines whether or not a cell is currently in play, and therefore is able to be moved/rotated
*/

class Cell {
private:
    sf::RectangleShape cover;
    bool active;
public: 
    const static sf::Vector2f cellDimensions; 
    const static sf::Vector2f miniCellDimensions; 
    Cell() = default; 
    Cell(sf::RectangleShape& cover_);
    ~Cell() = default; 
    bool isActive(); 
    bool setActive(bool active_); 
    
    sf::RectangleShape& getCover(); 
    sf::RectangleShape& setCover(sf::RectangleShape& newcover); 
};