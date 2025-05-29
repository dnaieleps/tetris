#include "../headers/piece.hpp"
#include <iostream>

Piece::Piece(int type_){
    type = type_;  
    sf::RectangleShape tempCover(Cell::cellDimensions); 
    pieceGrid = std::array<std::array<Cell*, 3>, 4>(); 

    
    for (auto &r : pieceGrid) {
        for (auto &cell : r) {
            tempCover.setFillColor(GRAY); 
            cell = new Cell(tempCover); 
        }
    }
    
    /****************************************************************************************
    *  visualization of the pieceGrid, where all of the piece types can be constructed from 
    *           [[*, *, *], 
    *            [*, *, *], 
    *            [*, *, *],
    *            [*, *, *],]
    *****************************************************************************************/

    // templates for all of the possible tetris pieces 
    sf::RectangleShape temp(Cell::cellDimensions);
    switch (type) {
        case 1: // I 
            temp.setFillColor(LIGHT_BLUE); 
            pieceGrid[0][1]->setCover(temp); 
            pieceGrid[1][1]->setCover(temp); 
            pieceGrid[2][1]->setCover(temp); 
            pieceGrid[3][1]->setCover(temp); 
            break; 
        case 2: // O
            temp.setFillColor(YELLOW); 
            pieceGrid[2][1]->setCover(temp);
            pieceGrid[2][2]->setCover(temp);
            pieceGrid[3][1]->setCover(temp);
            pieceGrid[3][2]->setCover(temp);
            break; 
        case 3: // L
            temp.setFillColor(ORANGE);
            pieceGrid[1][1]->setCover(temp);
            pieceGrid[2][1]->setCover(temp);
            pieceGrid[3][1]->setCover(temp);
            pieceGrid[3][2]->setCover(temp);
            break; 
        case 4: // J
            temp.setFillColor(DARK_BLUE);
            pieceGrid[1][1]->setCover(temp);
            pieceGrid[2][1]->setCover(temp);
            pieceGrid[3][1]->setCover(temp);
            pieceGrid[3][0]->setCover(temp);
            break; 
        case 5: // Z
            temp.setFillColor(RED);
            pieceGrid[2][0]->setCover(temp);
            pieceGrid[2][1]->setCover(temp);
            pieceGrid[3][1]->setCover(temp);
            pieceGrid[3][2]->setCover(temp);
            break;
        case 6: // S
            temp.setFillColor(GREEN);
            pieceGrid[3][0]->setCover(temp);
            pieceGrid[3][1]->setCover(temp);
            pieceGrid[2][1]->setCover(temp);
            pieceGrid[2][2]->setCover(temp);
            break; 
        case 7: // T
            temp.setFillColor(PURPLE);
            pieceGrid[2][1]->setCover(temp);
            pieceGrid[3][0]->setCover(temp);
            pieceGrid[3][1]->setCover(temp);
            pieceGrid[3][2]->setCover(temp);
            break; 
        default: // exception catcher
            temp.setFillColor(LIGHT_GRAY);
            for (auto &r : pieceGrid) {
                for (auto &cell : r) {
                    cell->setCover(temp); 
                }
            }
            break; 
    }
}
Piece::~Piece(){
    for (const auto &p : pieceGrid) {
        for (auto *cell : p) {
            delete cell; 
        }
    }
}
int Piece::getType() {
    return type; 
}
const std::array<std::array<Cell*, 3>, 4>& Piece::getPieceGrid() const {
    return pieceGrid; 
}
bool Piece::operator==(const Piece& other) {
    return type == other.type; 
}
