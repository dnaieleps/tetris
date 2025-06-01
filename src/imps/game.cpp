
#include "../headers/game.hpp"
#include <iostream>
#include <random>

Game::Game() {
    score = 0; 
    tickSpeed = 1; 
    paused = gameOver = justSwapped = false; 
    currentPiece = new Piece(0); 
    heldPiece = new Piece(0); 
    
    // initializing the pieceQueue
    for (int i = 0; i < 6; i++) {
        addRandomPieceToQueue(); 
    }

    // initializing empty cells across the grid with default cell color
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            sf::RectangleShape temp(Cell::cellDimensions); 
            temp.setFillColor(GRAY); 
            temp.setPosition(sf::Vector2f({static_cast<float>(30 + (j * 29 + j)), static_cast<float>(76 + (i * 29 + i))})); 

            grid[i][j] = new Cell(temp); 
        }
    }
}
Game::~Game() {
    delete currentPiece; 
    delete heldPiece; 

    while (!pieceQueue.empty()) {
        delete pieceQueue.front(); 
        pieceQueue.pop(); 
    }

    for (std::array<Cell*, 10> a : grid) {
        for (Cell* c : a) {
            delete c; 
        }
    }
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
Piece& Game::getCurrentPiece() {
    return *currentPiece; 
}
Piece& Game::getHeldPiece() {
    return *heldPiece; 
}
std::array<std::array<Cell*, 10>, 20>& Game::getGrid() {
    return grid; 
}
Piece& Game::getNextPiece() {
    return *pieceQueue.front(); 
}


void Game::addRandomPieceToQueue() {
    std::random_device rand; 
    std::mt19937 gen(rand()); 
    std::uniform_int_distribution<> distr(1, 7); 
    int randomNumber = distr(gen); 
    
    auto randomPiece = new Piece(randomNumber);
    pieceQueue.push(randomPiece); 
}
void Game::spawnPiece(Piece& piece) {
    // [0][3] == [0][0] (grid -> pieceGrid) (top left corner)
    // [3][5] == [3][2] (grid -> pieceGrid) (bottom right corner)
    
    int pRow = 0; int pCol = 0; 
    for (int i = 0; i < 4; i++) {
        pCol = 0; 
        for (int j = 3; j < 6; j++) {
            // sf::RectangleShape temp(Cell::cellDimensions);
            sf::RectangleShape temp(Cell::cellDimensions); 
            if (piece.getPieceGrid()[pRow][pCol] != nullptr) {
                temp.setFillColor(piece.getPieceGrid()[pRow][pCol]->getCover().getFillColor()); 
                temp.setPosition(grid[i][j]->getCover().getPosition());  
                
                grid[i][j]->setCover(temp);
                grid[i][j]->changeFilled();  
            }
            pCol++; 
        }
        pRow++; 
    }
}
void Game::swapHeldPiece() {
    if (justSwapped) {

    } else { 

    }
    
    justSwapped = !justSwapped; 
}
void Game::updateScore() {

} 
void Game::movePiece(sf::Keyboard::Scancode key) {

}
