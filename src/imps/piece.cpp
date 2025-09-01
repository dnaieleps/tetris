#include "../headers/piece.hpp"
#include <iostream>

// ***** PUBLIC MEMBER FUNCTIONS ***** 
Piece::Piece(int type_){
    type = type_;  
    rotation = 0; 
    degreesBasesAndGrids = std::unordered_map<u_int16_t, std::pair<std::array<int, 2>, std::array<std::array<Cell*, 4>, 4>>>(); 

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


    auto tempPair = std::pair<std::array<int, 2>, std::array<std::array<Cell*, 4>, 4>>({0, 0}, currentPieceGrid); 
    switch (type) {
        case 1: // I piece
            tempCover.setFillColor(LIGHT_BLUE); 

            // vertical rotations (symmetrical)
            currentPieceGrid[0][0] = new Cell(tempCover);                       //  [[1, 0, 0, 0], 
            currentPieceGrid[1][0] = new Cell(tempCover);                       //   [1, 0, 0, 0],
            currentPieceGrid[2][0] = new Cell(tempCover);                       //   [1, 0, 0, 0], 
            currentPieceGrid[3][0] = new Cell(tempCover);                       //   [1, 0, 0, 0]]

            tempPair.first = {1, 0};  tempPair.second = currentPieceGrid; 
            degreesBasesAndGrids[0] = tempPair; 

            tempPair.first = {2, 0};  tempPair.second = currentPieceGrid; 
            degreesBasesAndGrids[180] = tempPair; 
            clearGrid(cleanCover); 

            // horizontal rotations (symmetrical)
            currentPieceGrid[0][0] = new Cell(tempCover);                       //  [[1, 1, 1, 1],  
            currentPieceGrid[0][1] = new Cell(tempCover);                       //   [0, 0, 0, 0],  
            currentPieceGrid[0][2] = new Cell(tempCover);                       //   [0, 0, 0, 0],  
            currentPieceGrid[0][3] = new Cell(tempCover);                       //   [0, 0, 0, 0]]  

            tempPair.first = {0, 2};  tempPair.second = currentPieceGrid; 
            degreesBasesAndGrids[90] = tempPair; 

            tempPair.first = {0, 1};  tempPair.second = currentPieceGrid; 
            degreesBasesAndGrids[270] = tempPair;
            break; 
        case 2: // O piece
            tempCover.setFillColor(YELLOW); 
            
            // vertical and horizontal rotations (they're all the same lol)
            currentPieceGrid[0][0] = new Cell(tempCover);                       //  [[1, 1, 0, 0],  
            currentPieceGrid[0][1] = new Cell(tempCover);                       //   [1, 1, 0, 0],  
            currentPieceGrid[1][0] = new Cell(tempCover);                       //   [0, 0, 0, 0],  
            currentPieceGrid[1][1] = new Cell(tempCover);                       //   [0, 0, 0, 0]]  

            tempPair.first = {0, 0};  tempPair.second = currentPieceGrid; 
            degreesBasesAndGrids[0] = degreesBasesAndGrids[90] = degreesBasesAndGrids[180] = degreesBasesAndGrids[270] = tempPair; 
            break; 
        case 3: // L piece 
            tempCover.setFillColor(ORANGE); 

            currentPieceGrid[0][0] = new Cell(tempCover);                       //  [[1, 0, 0, 0],  
            currentPieceGrid[1][0] = new Cell(tempCover);                       //   [1, 0, 0, 0],  
            currentPieceGrid[2][0] = new Cell(tempCover);                       //   [1, 1, 0, 0],  
            currentPieceGrid[2][1] = new Cell(tempCover);                       //   [0, 0, 0, 0]]  
            tempPair.first = {1, 0};  tempPair.second = currentPieceGrid; 
            degreesBasesAndGrids[0] = tempPair; 
            clearGrid(cleanCover); 

            currentPieceGrid[1][0] = new Cell(tempCover);                       //  [[1, 1, 1, 0],  
            currentPieceGrid[0][0] = new Cell(tempCover);                       //   [1, 0, 0, 0],  
            currentPieceGrid[0][1] = new Cell(tempCover);                       //   [0, 0, 0, 0],  
            currentPieceGrid[0][2] = new Cell(tempCover);                       //   [0, 0, 0, 0]]  
            tempPair.first = {0, 1};  tempPair.second = currentPieceGrid; 
            degreesBasesAndGrids[90] = tempPair; 
            clearGrid(cleanCover);

            currentPieceGrid[0][0] = new Cell(tempCover);                       //  [[1, 1, 0, 0],  
            currentPieceGrid[0][1] = new Cell(tempCover);                       //   [0, 1, 0, 0],  
            currentPieceGrid[1][1] = new Cell(tempCover);                       //   [0, 1, 0, 0],  
            currentPieceGrid[2][1] = new Cell(tempCover);                       //   [0, 0, 0, 0]]  
            tempPair.first = {1, 1};  tempPair.second = currentPieceGrid; 
            degreesBasesAndGrids[180] = tempPair; 
            clearGrid(cleanCover); 

            currentPieceGrid[1][0] = new Cell(tempCover);                       //  [[0, 0, 1, 0],  
            currentPieceGrid[1][1] = new Cell(tempCover);                       //   [1, 1, 1, 0],  
            currentPieceGrid[1][2] = new Cell(tempCover);                       //   [0, 0, 0, 0],  
            currentPieceGrid[0][2] = new Cell(tempCover);                       //   [0, 0, 0, 0]]  
            tempPair.first = {1, 1};  tempPair.second = currentPieceGrid; 
            degreesBasesAndGrids[270] = tempPair;   
            break; 
        case 4: // J piece
            tempCover.setFillColor(DARK_BLUE);

            currentPieceGrid[2][0] = new Cell(tempCover);                       //  [[0, 1, 0, 0],  
            currentPieceGrid[2][1] = new Cell(tempCover);                       //   [0, 1, 0, 0],  
            currentPieceGrid[1][1] = new Cell(tempCover);                       //   [1, 1, 0, 0],  
            currentPieceGrid[0][1] = new Cell(tempCover);                       //   [0, 0, 0, 0]]  
            tempPair.first = {1, 1};  tempPair.second = currentPieceGrid; 
            degreesBasesAndGrids[0] = tempPair; 
            clearGrid(cleanCover); 

            currentPieceGrid[0][0] = new Cell(tempCover);                       //  [[1, 0, 0, 0],  
            currentPieceGrid[1][0] = new Cell(tempCover);                       //   [1, 1, 1, 0],  
            currentPieceGrid[1][1] = new Cell(tempCover);                       //   [0, 0, 0, 0],  
            currentPieceGrid[1][2] = new Cell(tempCover);                       //   [0, 0, 0, 0]]  
            tempPair.first = {1, 1};  tempPair.second = currentPieceGrid; 
            degreesBasesAndGrids[90] = tempPair; 
            clearGrid(cleanCover);
            
            currentPieceGrid[2][0] = new Cell(tempCover);                       //  [[1, 1, 0, 0],  
            currentPieceGrid[1][0] = new Cell(tempCover);                       //   [1, 0, 0, 0],  
            currentPieceGrid[0][0] = new Cell(tempCover);                       //   [1, 0, 0, 0],  
            currentPieceGrid[0][1] = new Cell(tempCover);                       //   [0, 0, 0, 0]]  
            tempPair.first = {1, 0};  tempPair.second = currentPieceGrid; 
            degreesBasesAndGrids[180] = tempPair; 
            clearGrid(cleanCover);

            currentPieceGrid[0][0] = new Cell(tempCover);                       //  [[1, 1, 1, 0],  
            currentPieceGrid[0][1] = new Cell(tempCover);                       //   [0, 0, 1, 0],  
            currentPieceGrid[0][2] = new Cell(tempCover);                       //   [0, 0, 0, 0],  
            currentPieceGrid[1][2] = new Cell(tempCover);                       //   [0, 0, 0, 0]]  
            tempPair.first = {0, 1};  tempPair.second = currentPieceGrid; 
            degreesBasesAndGrids[270] = tempPair; 
            break; 
        case 5: // Z piece
            tempCover.setFillColor(RED); 
            
            // horizontal rotations (symmetrical)
            currentPieceGrid[0][0] = new Cell(tempCover);                       //  [[1, 1, 0, 0],  
            currentPieceGrid[0][1] = new Cell(tempCover);                       //   [0, 1, 1, 0],  
            currentPieceGrid[1][1] = new Cell(tempCover);                       //   [0, 0, 0, 0],  
            currentPieceGrid[1][2] = new Cell(tempCover);                       //   [0, 0, 0, 0]]  

            tempPair.first = {0, 1};  tempPair.second = currentPieceGrid; 
            degreesBasesAndGrids[0] = tempPair; 

            tempPair.first = {1, 1};  tempPair.second = currentPieceGrid; 
            degreesBasesAndGrids[180] = tempPair; 
            clearGrid(cleanCover);

            // vertical rotations (symmetrical)
            currentPieceGrid[2][0] = new Cell(tempCover);                       //  [[0, 1, 0, 0],  
            currentPieceGrid[1][0] = new Cell(tempCover);                       //   [1, 1, 0, 0],  
            currentPieceGrid[1][1] = new Cell(tempCover);                       //   [1, 0, 0, 0],  
            currentPieceGrid[0][1] = new Cell(tempCover);                       //   [0, 0, 0, 0]]  

            tempPair.first = {1, 1};  tempPair.second = currentPieceGrid; 
            degreesBasesAndGrids[90] = tempPair; 

            tempPair.first = {1, 0};  tempPair.second = currentPieceGrid; 
            degreesBasesAndGrids[270] = tempPair; 
            break;
        case 6: // S piece
            tempCover.setFillColor(GREEN); 
            
            // vertical rotations 
            currentPieceGrid[1][0] = new Cell(tempCover);                       //  [[0, 1, 1, 0],  
            currentPieceGrid[1][1] = new Cell(tempCover);                       //   [1, 1, 0, 0],  
            currentPieceGrid[0][1] = new Cell(tempCover);                       //   [0, 0, 0, 0],  
            currentPieceGrid[0][2] = new Cell(tempCover);                       //   [0, 0, 0, 0]]  

            tempPair.first = {0, 1};  tempPair.second = currentPieceGrid; 
            degreesBasesAndGrids[0] = tempPair; 

            tempPair.first = {1, 1};  tempPair.second = currentPieceGrid; 
            degreesBasesAndGrids[180] = tempPair; 
            clearGrid(cleanCover);

            // horizontal rotations 
            currentPieceGrid[0][0] = new Cell(tempCover);                       //  [[1, 0, 0, 0],  
            currentPieceGrid[1][0] = new Cell(tempCover);                       //   [1, 1, 0, 0],  
            currentPieceGrid[1][1] = new Cell(tempCover);                       //   [0, 1, 0, 0],  
            currentPieceGrid[2][1] = new Cell(tempCover);                       //   [0, 0, 0, 0]]  

            tempPair.first = {1, 1};  tempPair.second = currentPieceGrid; 
            degreesBasesAndGrids[90] = tempPair; 

            tempPair.first = {1, 0};  tempPair.second = currentPieceGrid; 
            degreesBasesAndGrids[270] = tempPair; 
            break; 
        case 7: // T piece
            tempCover.setFillColor(PURPLE); 
            
            currentPieceGrid[2][0] = new Cell(tempCover);                       //  [[0, 1, 0, 0],  
            currentPieceGrid[2][1] = new Cell(tempCover);                       //   [1, 1, 1, 0],  
            currentPieceGrid[1][1] = new Cell(tempCover);                       //   [0, 0, 0, 0],  
            currentPieceGrid[0][1] = new Cell(tempCover);                       //   [0, 0, 0, 0]]  
            tempPair.first = {1, 1};  tempPair.second = currentPieceGrid; 
            degreesBasesAndGrids[0] = tempPair; 
            clearGrid(cleanCover); 

            currentPieceGrid[2][0] = new Cell(tempCover);                       //  [[0, 1, 0, 0],  
            currentPieceGrid[2][1] = new Cell(tempCover);                       //   [0, 1, 0, 0],  
            currentPieceGrid[1][1] = new Cell(tempCover);                       //   [1, 1, 0, 0],  
            currentPieceGrid[0][1] = new Cell(tempCover);                       //   [0, 0, 0, 0]]  
            tempPair.first = {1, 1};  tempPair.second = currentPieceGrid; 
            degreesBasesAndGrids[0] = tempPair; 
            clearGrid(cleanCover); 

            currentPieceGrid[2][0] = new Cell(tempCover);                       //  [[0, 1, 0, 0],  
            currentPieceGrid[2][1] = new Cell(tempCover);                       //   [0, 1, 0, 0],  
            currentPieceGrid[1][1] = new Cell(tempCover);                       //   [1, 1, 0, 0],  
            currentPieceGrid[0][1] = new Cell(tempCover);                       //   [0, 0, 0, 0]]  
            tempPair.first = {1, 1};  tempPair.second = currentPieceGrid; 
            degreesBasesAndGrids[0] = tempPair; 
            clearGrid(cleanCover); 

            currentPieceGrid[2][0] = new Cell(tempCover);                       //  [[0, 1, 0, 0],  
            currentPieceGrid[2][1] = new Cell(tempCover);                       //   [0, 1, 0, 0],  
            currentPieceGrid[1][1] = new Cell(tempCover);                       //   [1, 1, 0, 0],  
            currentPieceGrid[0][1] = new Cell(tempCover);                       //   [0, 0, 0, 0]]  
            tempPair.first = {1, 1};  tempPair.second = currentPieceGrid; 
            degreesBasesAndGrids[0] = tempPair;  
            break; 
        default: // exception catcher
            for (auto &r : currentPieceGrid) { 
                for (Cell* c : r) {
                    delete c; 
                    c = new Cell(tempCover); 
                }
            }
            tempPair.first = {0, 0};  tempPair.second = currentPieceGrid; 
            degreesBasesAndGrids[0] = degreesBasesAndGrids[90] = degreesBasesAndGrids[180] = degreesBasesAndGrids[270] = tempPair; 
            break; 
    }

    // setting the default starting pieceGrid to be the one at 0 degrees 
    currentPieceGrid = degreesBasesAndGrids[0].second;

    // setting the starting position of the Piece's center in relation to the mainGrid based on where it first spawns
    basisGlobalPos = {(0 + degreesBasesAndGrids[rotation].first[0]), (3 + degreesBasesAndGrids[rotation].first[1])}; 
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
const std::array<std::array<Cell*, 4>, 4>& Piece::getCurrentPieceGrid() {
    return currentPieceGrid; 
}
const std::array<int, 2>& Piece::getBasis() {
    return degreesBasesAndGrids[rotation].first;
}
const std::array<int, 2>& Piece::getBasisPos() {
    return basisGlobalPos; 
}

void Piece::setRotation(u_int16_t rotation_) {
    rotation = rotation_; 
    currentPieceGrid = degreesBasesAndGrids[rotation].second; 
}
void Piece::setBasisPos(const std::array<int, 2> &newPos) {
    basisGlobalPos = newPos; 
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
