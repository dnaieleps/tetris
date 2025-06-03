
#include "../headers/game.hpp"
#include <iostream>
#include <random>
#include <thread>

Game::Game() {
    score = 0; 
    tickSpeed = 1; 
    paused = gameOver = justSwapped = false; 
    heldPiece = new Piece(0); 
    
    // initializing the pieceQueue
    for (int i = 0; i < 6; i++) {
        addRandomPieceToQueue(); 
    }

    // initializing empty cells across the mainGrid with default cell color (all empty)
    for (int i = 0; i < mainGrid.size(); i++) {
        for (int j = 0; j < mainGrid[i].size(); j++) {
            sf::RectangleShape temp(Cell::cellDimensions); 
            temp.setFillColor(GRAY); 
            temp.setPosition(sf::Vector2f({static_cast<float>(30 + (j * 29 + j)), static_cast<float>(76 + (i * 29 + i))})); 

            mainGrid[i][j] = new Cell(temp); 
        }
    }
    
    // initializing the nextPieceGrid with default empty cell pieceGrid
    for (int i = 0 ; i < nextPieceGrid.size(); i++) {
        for (int j = 0; j < nextPieceGrid[i].size(); j++) {
            sf::RectangleShape temp(Cell::cellDimensions); 
            temp.setFillColor(GRAY); 
            temp.setPosition({static_cast<float>(405 + (j * 29 + j)), static_cast<float>(90 + (i * 29 + i))});

            nextPieceGrid[i][j] = new Cell(temp); 
        }
    }

    // initializing the next3PiecesGrid with default empty cell pieceGrids  400x240
    for (int i = 0; i < next3PiecesGrid.size(); i++) {
        for (int j = 0; j < next3PiecesGrid[i].size(); j++) {
            sf::RectangleShape temp(Cell::miniCellDimensions); 
            temp.setFillColor(GRAY); 
            temp.setPosition({static_cast<float>(420 + (j * 19 + j)), static_cast<float>(260 + (i * 19 + i))}); 

            next3PiecesGrid[i][j] = new Cell(temp); 
        }
    }

    // initializing the heldPieceGrid with default empty cell pieceGrid
    for (int i = 0; i < heldPieceGrid.size(); i++) {
        for (int j = 0; j < heldPieceGrid[i].size(); j++) {
            sf::RectangleShape temp(Cell::miniCellDimensions); 
            temp.setFillColor(GRAY); 
            temp.setPosition({static_cast<float>(420 + (j * 19 + j)), static_cast<float>(585 + (i * 19 + i))});

            heldPieceGrid[i][j] = new Cell(temp); 
        }
    }

    
}
Game::~Game() {
    delete currentPiece; 
    delete nextPiece; 
    delete heldPiece; 
    
    std::cout << "haii" << std::endl; // debuh

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
void Game::spawnPiece() {
    // [0][3] == [0][0] (grid -> pieceGrid) (top left corner)
    // [3][5] == [3][2] (grid -> pieceGrid) (bottom right corner) 
    std::queue<Piece*> temp = pieceQueue; 
    currentPiece = temp.front(); 
    temp.pop(); 

    int pRow = 0; int pCol = 0; 
    for (int i = 0; i < 4; i++) {
        pCol = 0; 
        for (int j = 3; j < 6; j++) {
            if (currentPiece->getPieceGrid()[pRow][pCol] != nullptr) {
                sf::RectangleShape temp(Cell::cellDimensions); 
                temp.setFillColor(currentPiece->getPieceGrid()[pRow][pCol]->getCover().getFillColor()); 
                temp.setPosition(mainGrid[i][j]->getCover().getPosition());  
                
                mainGrid[i][j]->setCover(temp);
                mainGrid[i][j]->changeFilled();  
            }
            pCol++; 
        }
        pRow++; 
    }

    
    // update each of the Piece pointers appropriately 
    nextPiece = temp.front(); 
    temp.pop(); 

    for (int i = 0; i < 3; i++) {
        next3Pieces[i] = temp.front(); 
        temp.pop(); 
    }
    for (Piece* p : next3Pieces) {
        std::cout << p->getType() << ", "; 
    }

    // spawn the pieceGrid of the nextPiece onto the nextPieceGrid
    for (int i = 0; i < nextPieceGrid.size(); i++) {
        for (int j = 0; j < nextPieceGrid[i].size(); j++) {
            if (nextPiece->getPieceGrid()[i][j] != nullptr) {
                sf::RectangleShape temp(Cell::cellDimensions); 
                temp.setFillColor(nextPiece->getPieceGrid()[i][j]->getCover().getFillColor()); 
                temp.setPosition(nextPieceGrid[i][j]->getCover().getPosition()); 

                nextPieceGrid[i][j]->setCover(temp); 
            }
        }
    }

    // spawn the pieceGrid of the next3Pieces array onto the next3PiecesGrid
    for (int i = 0; i < next3PiecesGrid.size(); i++) {
        for (int j = 0; j < 3; j++) {
            sf::RectangleShape temp1(Cell::miniCellDimensions); 
            sf::RectangleShape temp2(Cell::miniCellDimensions); 
            sf::RectangleShape temp3(Cell::miniCellDimensions); 

            // temp1.setFillColor(next3Pieces[0]->getPieceGrid()); ****************************************************************************************************
        }
    }
    std::cout << "yerr" << std::endl; 
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
