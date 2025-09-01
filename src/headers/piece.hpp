#pragma once
#include <SFML/Graphics.hpp>
#include "cell.hpp"

/******* COLOR CONSTANT DEFINITIONS *******/
#define GRAY sf::Color(57, 63, 78, 255)                      // board windows and sub-windows
#define LIGHT_GRAY sf::Color(343540)             // top row buttons and labels
#define LIGHT_BLUE sf::Color(82, 195, 225, 255)              // I piece
#define YELLOW sf::Color(226, 241, 97, 255)                  // O piece
#define ORANGE sf::Color(236, 169, 54, 255)                  // L piece
#define DARK_BLUE sf::Color(32, 85, 225, 255)                // J piece
#define RED sf::Color(225, 38, 38, 255)                      // Z piece
#define GREEN sf::Color(33, 172, 42, 255)                    // S piece
#define PURPLE sf::Color(104, 61, 212, 255)                  // T piece

/* class definition that serves as the blueprint for each of the Tetris pieces
*   @type -> a number that is unique to every kind of Tetris piece. There are only 7 types of pieces
*   @rotation -> unsigned integer that stores the orientation of the piece in degrees, where 0 is the base rotation
*   @basisCoords -> 2 element-long array that stores the {X, Y} coordinates of the basis point of the Piece, meaning that's where it's going to be drawn from 
*   @pieceGrid -> 2D array that represents the blueprint of how to make each specific piece
*   @rotationsAndBases -> ordered map that stores the 
*/

class Piece { 
private:
    u_int16_t type, rotation; 
    std::array<int, 2> basisGlobalPos; 
    std::array<std::array<Cell*, 4>, 4> currentPieceGrid;
    std::unordered_map<u_int16_t, std::pair<std::array<int, 2>, std::array<std::array<Cell*, 4>, 4>>> degreesBasesAndGrids; 

public:
    Piece() = default;
    Piece(int type_);
    ~Piece();

    int getType(); 
    u_int16_t getRotation(); 
    const std::array<std::array<Cell*, 4>, 4>& getCurrentPieceGrid();
    const std::array<int, 2>& getBasis();  
    const std::array<int, 2>& getBasisPos(); 

    void setRotation(u_int16_t rotation_); 
    void setBasisPos(const std::array<int, 2> &newPos); 

    void clearGrid(sf::RectangleShape cover); 
    bool operator==(const Piece& other); 
};