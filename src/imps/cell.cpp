#include "../headers/cell.hpp"

Cell::Cell() {

}
Cell::~Cell() { 

}
bool Cell::getFilled() {
    return filled; 
}
bool Cell::changeFilled() {
    filled = !filled; 
    return filled; 
}