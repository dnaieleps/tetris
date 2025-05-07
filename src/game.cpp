#include "game.hpp"
#include <random>

Game::Game() {
    score = 0; 
    tickSpeed = 1; 
    paused = gameOver = false; 
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
    if(heldPiece == nullptr) {
        *heldPiece = *currentPiece; 
        *currentPiece = pieceQueue->front();
        pieceQueue->pop();
        pieceQueue->push(generateNewPiece());
    } else { 
        Piece temp = *heldPiece;
        *heldPiece = *currentPiece; 
        *currentPiece = temp; 
        currentPiece->changeSwapped();
    }
}
void Game::updateScore() {

}