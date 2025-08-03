#include "../headers/piece.hpp"
#include <iostream>

Piece::Piece(int type_){
    type = type_;  
    sf::RectangleShape tempCover(Cell::cellDimensions); 
    pieceGridRotations = std::array<std::vector<std::vector<Cell*>>, 4>(); 

    // characteristics of the default light gray cell in which each pieceGrid will initially be filled with 
    sf::RectangleShape temp(Cell::cellDimensions);
    temp.setFillColor(LIGHT_GRAY);
    Cell *tempCell = new Cell(temp);
    tempCell->setActive(false); 
    currentPieceGrid = std::vector<std::vector<Cell*>>(); 
    sf::RectangleShape fillCover(Cell::cellDimensions);
    
    switch (type) {
        case 1: // I (only 2 blueprints needed)
            // structuring 
            for (int i = 0; i < 1; i++) {
                std::vector<Cell*> tempRow; 
                for (int j = 0; j < 4; j++) {
                    tempRow.push_back(tempCell); 
                }
                currentPieceGrid.push_back(tempRow); 
            }

            // filling in the piece's filled spots 
            fillCover.setFillColor(LIGHT_BLUE);

            currentPieceGrid[0][0]->setCover(fillCover); 
            currentPieceGrid[0][0]->setActive(true); 

            /* I PIECE'S PIECEGRIDS: 
            *
            *
            * 
            * 
            */

            pieceGridRotations[0] = currentPieceGrid;
            pieceGridRotations[1] = currentPieceGrid;
            pieceGridRotations[2] = currentPieceGrid;
            pieceGridRotations[3] = currentPieceGrid;
            break; 
        case 2: // O ()
            
            break; 
        case 3: // L
            
            break; 
        case 4: // J
            
            break; 
        case 5: // Z
            
            break;
        case 6: // S
            
            break; 
        case 7: // T
            
            break; 
        default: // exception catcher
            
            break; 
    }

    currentPieceGrid = pieceGridRotations[0]; 
    delete tempCell; 
}
Piece::~Piece(){
    for (const auto &p : currentPieceGrid) {
        for (auto *cell : p) {
            delete cell; 
        }
    }
}
int Piece::getType() {
    return type; 
}
const std::vector<std::vector<Cell*>>& Piece::getCurrentPieceGrid() const {
    return currentPieceGrid; 
}
bool Piece::operator==(const Piece& other) {
    return type == other.type; 
}
