#include "../headers/game.hpp"
#include <random>
#include <iostream>

Game::Game() {
    score = 0; 
    tickSpeed = 1; 
    paused = gameOver = justSwapped = false; 
    pieceQueue = new std::queue<Piece>();
    
    // initializing empty cells across the grid with default cell color 
    grid = new std::array<std::array<Cell*, 10>, 20>();
    for (int i = 0; i < grid->size(); i++) {
        for (int j = 0; j < (*grid)[i].size(); j++) {
            sf::RectangleShape temp({29, 29}); 
            temp.setFillColor(sf::Color(73, 80, 89, 128)); 
            temp.setSize(Cell::cellDimensions); 
            temp.setPosition(sf::Vector2f({static_cast<float>(30 + (j * 29 + j)), static_cast<float>(76 + (i * 29 + i))})); 

            (*grid)[i][j] = new Cell(temp); 
        }
    }
}
Game::~Game() {
    for (std::array<Cell*, 10> row : *grid) {
        for(Cell *t : row) {
            delete t;  
        }
    }
    delete grid; 
    delete pieceQueue; 
    delete currentPiece; 
    delete heldPiece; 
}
int Game::getScore() {
    return score;
}
int Game::increaseScore(int amt) {
    return score += amt;
}
int Game::getTickSpeed() {
    return tickSpeed; 
}
int Game::setTickSpeed(int amt) {
    return tickSpeed = amt; 
}
bool Game::isPaused() {
    return paused; 
}
bool Game::changePause() {
    paused = !paused; 
    return paused; 
}
bool Game::gameIsOver() {
    return gameOver;
}
bool Game::changeGameOver() {
    gameOver = !gameOver; 
    return gameOver; 
}
bool Game::hasJustSwapped() {
    return justSwapped; 
}
Piece Game::getCurrentPiece() {
    return *currentPiece; 
}
Piece Game::generateNewPiece() {
    std::random_device rand; 
    std::mt19937 generator(rand());
    std::uniform_int_distribution<int> distribution(0, 6);
    int randomPiece = distribution(generator);
    
    return Piece(randomPiece); 
}
Piece Game::getNextPiece() {
    if(pieceQueue->empty()) {
        return Piece(-1);
    } 

    Piece top = pieceQueue->front();
    pieceQueue->pop();
    return top;
}
void Game::swapHeldPiece() {
    Piece* emptyPiece = new Piece(0); 
    if(heldPiece == emptyPiece) {
        *heldPiece = *currentPiece; 
        *currentPiece = pieceQueue->front();
        pieceQueue->pop();
        pieceQueue->push(generateNewPiece());
    } else { 
        Piece temp = *heldPiece;
        *heldPiece = *currentPiece; 
        *currentPiece = temp; 
        
    }
    
    delete emptyPiece; 
}
void Game::updateScore() {

}
std::array<std::array<Cell*, 10>, 20>& Game::getGrid() {
    return *grid; 
}
void Game::spawnPiece(Piece& piece) {
    // [0][3] == [0][0] (grid -> pieceGrid) (top left corner)
    // [3][5] == [3][2] (grid -> pieceGrid) (bottom right corner)
    std::array<std::array<Cell*, 3>, 4>* temp = piece.getPieceGrid(); 
    
    int pRow = 0; int pCol = 0; 
    for (int i = 0; i < 4; i++) {
        for (int j = 3; j < 6; j++) {
            (*grid)[i][j] = (*temp)[pRow][pCol]; 
            pCol++; 
        }
        pRow++; 
    }

    delete temp; 
}
void Game::movePiece(sf::Keyboard::Scancode key) {

}