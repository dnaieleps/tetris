#pragma once
#ifndef PIECE_H
#define PIECE_H

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
*   @pieceGrid ->
*   @color ->
*   @placed ->
*
*/
class Piece { 
private:
    bool* pieceGrid[3][4];
    sf::Color* color; 
    bool placed; 

public:
    Piece();
    Piece(int type);
    ~Piece();
};


#endif