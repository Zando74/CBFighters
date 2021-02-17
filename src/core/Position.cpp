#include "Position.h"
#include <iostream>

using namespace std;

Position::Position() {}
Position::~Position() {}

int Position::getPosX() { return x; }

int Position::getPosY() { return y; }

void Position::setPosX(const int & posX) {x = posX;}

void Position::setPosY(const int & posY) {y = posY;}

void Position::moveRight() { x = (x+4); }
void Position::moveLeft() { x = (x-4); }
void Position::forwardJump() { x++; y++; }
void Position::neutralJump() { y++; }
void Position::backwardJump() {x--; y--; }
