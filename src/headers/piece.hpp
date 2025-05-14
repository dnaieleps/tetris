#pragma once
#include <SFML/Graphics.hpp>

/******* COLOR CONSTANT DEFINITIONS *******/
#define GRAY sf::Color(57, 63, 78, 255)                      // board windows and sub-windows
#define LIGHT_GRAY sf::Color(119, 119, 128, 255)             // top row buttons and labels
#define LIGHT_BLUE sf::Color(82, 195, 225, 255)              // I piece
#define YELLOW sf::Color(226, 241, 97, 255)                  // O piece
#define ORANGE sf::Color(236, 169, 54, 255)                  // L piece
#define DARK_BLUE sf::Color(32, 85, 225, 255)                // J piece
#define RED sf::Color(225, 38, 38, 255)                      // Z piece
#define GREEN sf::Color(33, 172, 42, 255)                    // S piece
#define PURPLE sf::Color(104, 61, 212, 255)                  // T piece


/* class definition that serves as the blueprint for each of the Tetris pieces
*   @pieceGrid -> 2D array that represents the blueprint of how to make each specific piece
*   @color -> sf::Color attribute that just represents the color of the tetris piece
*   @inPlay -> boolean representing whether or not the tetris piece is currently in play 
*   @justSwapped -> boolean representing whether or not the Piece in question has just been swapped, preventing swap spamming
*/
class Piece { 
private:
    int type;
    bool* pieceGrid[3][4];
    sf::Color* color; 
    bool inPlay; 

public:
    Piece();
    Piece(int type);
    ~Piece();
    int getType(); 
    bool* getPieceGrid();
    bool operator==(const Piece& other); 
};