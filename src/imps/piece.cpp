#include "../headers/piece.hpp"
#include <iostream>

// ***** PUBLIC MEMBER FUNCTIONS ***** 
Piece::Piece(int type_){
    type = type_;  
    rotation = 0; 
    pieceGridRotations = std::array<std::array<std::array<Cell*, 4>, 4>, 4>(); 

    // characteristics of the default light gray cell in which each pieceGrid will initially be filled with 
    sf::RectangleShape tempCover(Cell::cellDimensions);
    tempCover.setFillColor(GRAY);  
    auto cleanCover = tempCover; // used to clean the grid everytime a new "costume" is being created

    // initialization of the currentPieceGrid
    currentPieceGrid = std::array<std::array<Cell*, 4>, 4>(); 
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            currentPieceGrid[i][j] = new Cell(tempCover); 
        }
    }
    
    switch (type) {
        case 1: // I piece
            tempCover.setFillColor(LIGHT_BLUE); 

            // vertical rotations
            currentPieceGrid[0][0] = new Cell(tempCover);                       //  [[1, 0, 0, 0], 
            currentPieceGrid[1][0] = new Cell(tempCover);                       //   [1, 0, 0, 0],
            currentPieceGrid[2][0] = new Cell(tempCover);                       //   [1, 0, 0, 0], 
            currentPieceGrid[3][0] = new Cell(tempCover);                       //   [1, 0, 0, 0]]
            pieceGridRotations[0] = pieceGridRotations[2] = currentPieceGrid; 
            clearGrid(cleanCover); 

            // horizontal rotations
            currentPieceGrid[0][0] = new Cell(tempCover);                       //  [[1, 1, 1, 1],  
            currentPieceGrid[0][1] = new Cell(tempCover);                       //   [0, 0, 0, 0],  
            currentPieceGrid[0][2] = new Cell(tempCover);                       //   [0, 0, 0, 0],  
            currentPieceGrid[0][3] = new Cell(tempCover);                       //   [0, 0, 0, 0]]  
            pieceGridRotations[1] = pieceGridRotations[3] = currentPieceGrid; 
            break; 
        case 2: // O piece
            tempCover.setFillColor(YELLOW); 
            
            // vertical and horizontal rotations (they're all the same lol)
            currentPieceGrid[0][0] = new Cell(tempCover);                       //  [[1, 1, 0, 0],  
            currentPieceGrid[0][1] = new Cell(tempCover);                       //   [1, 1, 0, 0],  
            currentPieceGrid[1][0] = new Cell(tempCover);                       //   [0, 0, 0, 0],  
            currentPieceGrid[1][1] = new Cell(tempCover);                       //   [0, 0, 0, 0]]  
            pieceGridRotations[0] = pieceGridRotations[1] = pieceGridRotations[2]  = pieceGridRotations[3] = currentPieceGrid; 
            break; 
        case 3: // L piece 
            tempCover.setFillColor(ORANGE); 

            // vertical rotations
            currentPieceGrid[0][0] = new Cell(tempCover);                       //  [[1, 0, 0, 0],  
            currentPieceGrid[1][0] = new Cell(tempCover);                       //   [1, 0, 0, 0],  
            currentPieceGrid[2][0] = new Cell(tempCover);                       //   [1, 1, 0, 0],  
            currentPieceGrid[2][1] = new Cell(tempCover);                       //   [0, 0, 0, 0]]  
            pieceGridRotations[0] = currentPieceGrid; 
            clearGrid(cleanCover); 

            currentPieceGrid[0][0] = new Cell(tempCover);                       //  [[1, 1, 0, 0],  
            currentPieceGrid[0][1] = new Cell(tempCover);                       //   [0, 1, 0, 0],  
            currentPieceGrid[1][1] = new Cell(tempCover);                       //   [0, 1, 0, 0],  
            currentPieceGrid[2][1] = new Cell(tempCover);                       //   [0, 0, 0, 0]]  
            pieceGridRotations[2] = currentPieceGrid; 
            clearGrid(cleanCover); 

            // horizontal rotations
            currentPieceGrid[1][0] = new Cell(tempCover);                       //  [[0, 0, 1, 0],  
            currentPieceGrid[1][1] = new Cell(tempCover);                       //   [1, 1, 1, 0],  
            currentPieceGrid[1][2] = new Cell(tempCover);                       //   [0, 0, 0, 0],  
            currentPieceGrid[0][2] = new Cell(tempCover);                       //   [0, 0, 0, 0]]  
            pieceGridRotations[1] = currentPieceGrid; 
            clearGrid(cleanCover); 

            currentPieceGrid[1][0] = new Cell(tempCover);                       //  [[1, 1, 1, 0],  
            currentPieceGrid[0][0] = new Cell(tempCover);                       //   [1, 0, 0, 0],  
            currentPieceGrid[0][1] = new Cell(tempCover);                       //   [0, 0, 0, 0],  
            currentPieceGrid[0][2] = new Cell(tempCover);                       //   [0, 0, 0, 0]]  
            pieceGridRotations[3] = currentPieceGrid; 
            break; 
        case 4: // J piece
            tempCover.setFillColor(DARK_BLUE);
            
            break; 
        case 5: // Z piece
            tempCover.setFillColor(RED); 
            
            break;
        case 6: // S piece
            tempCover.setFillColor(GREEN); 
            
            break; 
        case 7: // T piece
            tempCover.setFillColor(PURPLE); 
            
            break; 
        default: // exception catcher
            
            break; 
    }

    currentPieceGrid = pieceGridRotations[0];
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
u_int16_t Piece::getRotation() {
    return rotation; 
}
const std::array<std::array<Cell*, 4>, 4>& Piece::getCurrentPieceGrid() const {
    return currentPieceGrid; 
}

void Piece::setRotation(int rotation_) {
    rotation = rotation_;
    currentPieceGrid = pieceGridRotations[rotation / 90]; 
}

bool Piece::operator==(const Piece& other) {
    return type == other.type; 
}

void Piece::clearGrid(sf::RectangleShape cover) {
    for (int i = 0; i < currentPieceGrid.size(); i++) {
        for (int j = 0; j < currentPieceGrid[i].size(); j++) {
            currentPieceGrid[i][j] = new Cell(cover); 
        }
    }
}
