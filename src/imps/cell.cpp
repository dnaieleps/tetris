#include "../headers/cell.hpp"

const sf::Vector2f Cell::cellDimensions = sf::Vector2f({28, 28}); 
const sf::Vector2f Cell::miniCellDimensions = sf::Vector2f({19, 19}); 

Cell::Cell(sf::RectangleShape& cover_) {
    cover = cover_; 
    filled = false; 
}
bool Cell::isFilled() {
    return filled; 
}
bool Cell::changeFilled() {
    filled = !filled; 
    return filled; 
}
sf::RectangleShape& Cell::getCover() {
    return cover; 
}
sf::RectangleShape& Cell::setCover(sf::RectangleShape& newcover) {
    cover = newcover; 
    return cover; 
}