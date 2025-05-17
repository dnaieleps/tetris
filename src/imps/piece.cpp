#include "../headers/piece.hpp"

Piece::Piece(int type_){
    type = type_;  
    sf::Color* tempColor; 


    /* visualization of the pieceGrid, where all of the piece types can be constructed from 
    *           [[*, *, *], 
    *            [*, *, *], 
    *            [*, *, *],
    *            [*, *, *],]
    */
    switch (type) {
        case 0: // "empty" piece (used for default heldpiece Piece)
            tempColor = new LIGHT_GRAY;
        case 1: // I 
            tempColor = new LIGHT_BLUE; 
            (*pieceGrid)[0][1]->getCover().setFillColor(*tempColor); 
            (*pieceGrid)[1][1]->getCover().setFillColor(*tempColor); 
            (*pieceGrid)[2][1]->getCover().setFillColor(*tempColor); 
            (*pieceGrid)[3][1]->getCover().setFillColor(*tempColor); 

            (*pieceGrid)[0][1]->changeFilled();  
            (*pieceGrid)[1][1]->changeFilled();  
            (*pieceGrid)[2][1]->changeFilled();  
            (*pieceGrid)[3][1]->changeFilled();  
        case 2: // O
            tempColor = new YELLOW;
        case 3: // L
            tempColor = new ORANGE;
        case 4: // J 
            tempColor = new DARK_BLUE;
        case 5: // Z
            tempColor = new RED;
        case 6: // S
            tempColor = new GREEN;
        case 7: // T
            tempColor = new PURPLE;
        default: // exception catcher
    }

    delete tempColor; 
}
Piece::~Piece(){
    delete pieceGrid; 
    delete color; 
}
int Piece::getType() {
    return type; 
}
std::array<std::array<Cell*, 3>, 4>* Piece::getPieceGrid() {
    return pieceGrid; 
}
bool Piece::operator==(const Piece& other) {
    return type == other.type; 
}
