#include "piece.hpp"

Piece::Piece() {

}
Piece::Piece(int type){

}
Piece::~Piece(){

}

bool Piece::hasJustSwapped() {
    return justSwapped; 
}
bool Piece::changeSwapped() {
    justSwapped = !justSwapped; 
    return justSwapped; 
}