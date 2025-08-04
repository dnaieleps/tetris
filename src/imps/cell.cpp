#include "../headers/cell.hpp"

// ***** PUBLIC MEMBER CONSTANTS ***** 
const sf::Vector2f Cell::cellDimensions = sf::Vector2f({28, 28}); 
const sf::Vector2f Cell::miniCellDimensions = sf::Vector2f({19, 19}); 

// ***** PUBLIC MEMBER FUNCTIONS ***** 
Cell::Cell(sf::RectangleShape& cover_) {
    cover = cover_; 
    active = false; 
}
bool Cell::isActive() {
    return active; 
}
bool Cell::setActive(bool active_) {
    active = active_; 
    return active; 
}

sf::RectangleShape& Cell::getCover() {
    return cover; 
}
sf::RectangleShape& Cell::setCover(sf::RectangleShape& newcover) {
    cover = newcover; 
    return cover; 
}