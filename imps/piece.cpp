#include "../headers/piece.hpp"

Piece::Piece() {

}
Piece::Piece(int type){

}
Piece::~Piece(){

}
int Piece::getType() {
    return type; 
}
bool Piece::operator==(const Piece& other) {
    return this->type == other.type; 
}
