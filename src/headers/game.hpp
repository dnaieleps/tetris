#pragma once
#include <queue>
#include "piece.hpp"
#include "cell.hpp"

/* class definition that serves as a blueprint to the Game object, where all of the games mechanics will be found
*   @pieceQueue -> queue of Piece objects which represents the pieces that are going to be played next
*   @currentPiece -> represents the Piece which is currently being used in play 
*   @heldPiece -> represents the Piece which is currently being held in the Tetris hold box
*   @grid -> 2d std::array that represents the game grid that overlays the main board
*   @score -> represents the current game score. 1 point will be awarded for every tick survived, 30 for every line cleared, and 100 points for every tetris 
*   @tickSpeed -> represents the speed in which the pieces will move down the screen. the integer value indicates how many ticks will occur in 1 second
*   @paused -> boolean representing whether or not the game is paused, setting the tickSpeed to 0 and will resume to normal when unpaused
*   @gameOver -> boolean representing whether or not the game is over, ending when a Piece exceeds the top of the board (ArrayOutofBoundsException)
*   @justSwapped -> boolean representing whether or not the piece in question was just swapped out of the held box, preventing swap spamming
*/
class Game {
private:
    int score;
    int tickSpeed;
    bool paused, gameOver, justSwapped;
    Piece *currentPiece, *nextPiece, *heldPiece;
    std::array<Piece*, 3> next3Pieces; 
    std::vector<std::vector<Cell*>> playGrid; 

public: 
    std::queue<Piece*> pieceQueue; 
    std::array<std::array<Cell*, 10>, 20> mainGrid; 
    std::array<std::array<Cell*, 3>, 4> nextPieceGrid, heldPieceGrid; 
    std::array<std::array<Cell*, 3>, 14> next3PiecesGrid; 

    Game(); // Game constructor
    ~Game(); // Game destructor 
    int getScore(); // returns current player score
    int increaseScore(int amt); // increments player score by given amount
    int getTickSpeed(); // returns game's current tick speed
    int setTickSpeed(int amt); // changes the tick speed to the specified amount to increase/decrease difficulty
    bool isPaused(); // returns whether or not the game is paused 
    bool changePause(); // switches to either paused or unpaused depending on its previous state
    bool gameIsOver(); // returns whether or not the game is over, meaning the player lost
    bool changeGameOver(); // changes the gameOver variable to be true, ending the game
    bool hasJustSwapped(); // returns whether or not the player has just swapped a piece. put in place so you can't spam swap
    Piece& getCurrentPiece(); // returns the current piece in play 
    Piece& getHeldPiece(); // returns the held piece in the held box (bottom right)
    std::array<std::array<Cell*, 10>, 20>& getGrid(); // returns the address of the game grid 
    Piece& getNextPiece(); // pops the top value off of the pieceQueue to be displayed onto the game screen
    void addRandomPieceToQueue(); // helper function that adds a random Piece to the pieceQueue
    void swapHeldPiece(); // swaps the held piece with the piece that is currently in play
    void updateScore(); // updates the score every gametick
    void spawnPiece(); // copies piece from top of the pieceQueue onto the mainGrid, while also updating every other game block
    void movePiece(const sf::Keyboard::Scancode &key); // moves the copied piece along the board as signified by the arrow that is entered
    void update(); // handles recoordinating the new tile positions, updating score, checking game state, etc
};