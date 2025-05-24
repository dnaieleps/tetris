#include "../headers/piece.hpp"

Piece::Piece(int type_){
    type = type_;  
    sf::Color tempColor; 
    sf::RectangleShape tempCover; 
    pieceGrid = std::array<std::array<std::unique_ptr<Cell>, 3>, 4>(); 

    /* visualization of the pieceGrid, where all of the piece types can be constructed from 
    *           [[*, *, *], 
    *            [*, *, *], 
    *            [*, *, *],
    *            [*, *, *],]
    */
    switch (type) {
        case 0: // "empty" piece (used for default heldpiece Piece)
            tempColor = LIGHT_GRAY;
            tempCover.setFillColor(tempColor);  

            for (auto &a : pieceGrid) {
                for (auto &cell : a) {
                    cell = std::make_unique<Cell>(tempCover); 
                }
            }
            break; 
        case 1: // I 
            tempColor = LIGHT_BLUE; 
            break; 
        case 2: // O
            tempColor = YELLOW;
            break; 
        case 3: // L
            tempColor = ORANGE;
            break; 
        case 4: // J 
            tempColor = DARK_BLUE;
            break; 
        case 5: // Z
            tempColor = RED;
            break; 
        case 6: // S
            tempColor = GREEN;
            break; 
        case 7: // T
            tempColor = PURPLE;
            break; 
        default: // exception catcher
            tempColor = LIGHT_GRAY; 
            break; 
    }
}
Piece::~Piece(){
    delete color; 
}
int Piece::getType() {
    return type; 
}
const std::array<std::array<std::unique_ptr<Cell>, 3>, 4>& Piece::getPieceGrid() const {
    return pieceGrid; 
}
bool Piece::operator==(const Piece& other) {
    return type == other.type; 
}
