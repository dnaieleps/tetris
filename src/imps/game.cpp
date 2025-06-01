
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

    // initializing empty cells across the mainGrid with default cell color
    for (int i = 0; i < mainGrid.size(); i++) {
        for (int j = 0; j < mainGrid[i].size(); j++) {
            sf::RectangleShape temp(Cell::cellDimensions); 
            temp.setFillColor(GRAY); 
            temp.setPosition(sf::Vector2f({static_cast<float>(30 + (j * 29 + j)), static_cast<float>(76 + (i * 29 + i))})); 

            mainGrid[i][j] = new Cell(temp); 
        }
    }

    // initializing the nextPieceGrid with default cell colors 
    for (int i = 0 ; i < nextPieceGrid.size(); i++) {
        for (int j = 0; j < nextPieceGrid[i].size(); j++) {
            sf::RectangleShape temp(Cell::cellDimensions); 
            temp.setFillColor(GREEN); 
            temp.setPosition({static_cast<float>(405 + (j * 29 + j)), static_cast<float>(90 + (i * 29 + i))});

            nextPieceGrid[i][j] = new Cell(temp); 
        }
    }

    // initializing the next3PiecesGrid with default cell colors
    

    // initializing the heldPieceGrid with default cell colors
}
Game::~Game() {
    delete currentPiece; 
    delete heldPiece; 

    // pieceQueue destructor 
    while (!pieceQueue.empty()) {
        delete pieceQueue.front(); 
        pieceQueue.pop(); 
    }

    // mainGrid destructor 
    for (std::array<Cell*, 10> a : mainGrid) {
        for (Cell* c : a) {
            delete c; 
        }
    }

    // nextPieceGrid destructor 
    for (std::array<Cell*, 3> &row : nextPieceGrid) {
        for (Cell* c : row) {
            delete c; 
        }
    }
    
    // next3PiecesGrid destructor 
    for (std::array<Cell*, 3> &row : next3PiecesGrid) {
        for (Cell* c : row) {
            delete c; 
        }
    }

    // heldPieceGrid destructor 
    for (std::array<Cell*, 3> &row : heldPieceGrid) {
        for (Cell* c : row) {
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
    return mainGrid; 
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
void Game::spawnPiece(Piece& piece, int gridID) {
    // piece parameter holds the piece to be copied to the respective grid 
    // gridID parameter represents one of the 4 places that the piece can be drawn to: 1 (main grid), 2 (nextPiece), 3 (next3Pieces), 4 (heldPiece)
    int pRow = 0; int pCol = 0; 
    switch (gridID) {
        case 1: // main gameplay grid 
            // [0][3] == [0][0] (grid -> pieceGrid) (top left corner)
            // [3][5] == [3][2] (grid -> pieceGrid) (bottom right corner) 
            for (int i = 0; i < 4; i++) {
                pCol = 0; 
                for (int j = 3; j < 6; j++) {
                    // sf::RectangleShape temp(Cell::cellDimensions);
                    sf::RectangleShape temp(Cell::cellDimensions); 
                    if (piece.getPieceGrid()[pRow][pCol] != nullptr) {
                        temp.setFillColor(piece.getPieceGrid()[pRow][pCol]->getCover().getFillColor()); 
                        temp.setPosition(mainGrid[i][j]->getCover().getPosition());  
                        
                        mainGrid[i][j]->setCover(temp);
                        mainGrid[i][j]->changeFilled();  
                    }
                    pCol++; 
                }
                pRow++; 
            }
            pCol = pRow = 0; 
            break; 
        case 2: // nextPiece grid
            break; 
        case 3: // next3Pieces grid
            break; 
        case 4: // heldPiece grid 
            break; 
        default: 
            std::cerr << "invalid gridID!!! >:(";
            break; 
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
