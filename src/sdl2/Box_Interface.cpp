//
// Created by constantin on 24/04/2020.
//

#include "Box_Interface.h"

Box_Interface::Box_Interface(SDL_Renderer *ren) : Interface_Element(ren){
    DrawBox.x=10;
    DrawBox.y=10;
    DrawBox.w=20;
    DrawBox.h=10;
    setColor();
}

Box_Interface::~Box_Interface(){}

void Box_Interface::setSize(const int & w, const int & h){
    DrawBox.w= w;
    DrawBox.h= h;
}

void Box_Interface::setDrawPos(const int & x, const int & y){
    DrawBox.x=x;
    DrawBox.y=y;
}

void Box_Interface::setColor(const int &r, const int &g,const int &b){
    R=r;
    G=g;
    B=b;
}


void Box_Interface::drawBox(){}