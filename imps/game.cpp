#include "../headers/game.hpp"
#include <random>

Game::Game() {
    score = 0; 
    tickSpeed = 1; 
    paused = gameOver = justSwapped = false; 
    pieceQueue = new std::queue<Piece>();
}
Game::~Game() {
    delete pieceQueue;
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

    Piece* piece = new Piece(randomPiece); 
    return *piece; 
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
    std::unique_ptr<Piece> emptyPiece = std::make_unique<Piece>(0); 
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
}
void Game::updateScore() {

}