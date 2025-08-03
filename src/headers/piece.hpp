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
*   @pieceGrid -> 2D array that represents the blueprint of how to make each specific piece
*   @pieceGridRotations -> as opposed to actually doing matrix multiplication to rotate the pieces, 
    i'm just making them different rotated versions of themselves stored in this array because i don't know how to do that yet 
*/

class Piece { 
private:
    int type;
    int center[2]; 
    std::vector<std::vector<Cell*>> currentPieceGrid;
    std::array<std::vector<std::vector<Cell*>>, 4> pieceGridRotations; 

public:
    Piece() = default;
    Piece(int type_);
    ~Piece();
    int getType(); 
    const std::vector<std::vector<Cell*>>& getCurrentPieceGrid() const;
    bool operator==(const Piece& other); 
};