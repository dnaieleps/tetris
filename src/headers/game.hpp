#pragma once
#include <queue>
#include "piece.hpp"
#include "cell.hpp"

/* class definition that serves as a blueprint to the Game object, where all of the games mechanics will be found
*   @pieceQueue -> queue of Piece objects which represents the pieces that are going to be played next
*   @currentPiece -> represents the Piece which is currently being used in play 
*   @heldPiece -> represents the Piece which is currently being held in the Tetris hold box
*   @grid -> represents the tetris gameboard where each Cell represents a grid tile on the gameboard
*   @score -> represents the current game score. 1 point will be awarded for every tick survived, 30 for every line cleared, and 100 points for every tetris 
*   @tickSpeed -> represents the speed in which the pieces will move down the screen. the integer value indicates how many ticks will occur in 1 second
*   @paused -> boolean representing whether or not the game is paused, setting the tickSpeed to 0 and will resume to normal when unpaused
*   @gameOver -> boolean representing whether or not the game is over, ending when a Piece exceeds the top of the board (ArrayOutofBoundsException)
*   @justSwapped -> boolean representing whether or not the piece in question was just swapped out of the held box, preventing swap spamming
*/
class Game {
private: 
    std::queue<Piece>* pieceQueue; 
    std::unique_ptr<Piece> currentPiece, heldPiece; 
    Cell grid[24][10]; 
    int score;
    int tickSpeed;
    bool paused, gameOver, justSwapped;

public: 
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
    Piece getCurrentPiece(); // returns the current piece in play 
    Piece getNextPiece(); // pops the top value off of the pieceQueue to be displayed onto the game screen
    Piece generateNewPiece(); // generates a new piece to be added to the back of the pieceQueue to maintain constant queue size
    void swapHeldPiece(); // swaps the held piece with the piece that is currently in play
    void updateScore(); // updates the score every gametick
};