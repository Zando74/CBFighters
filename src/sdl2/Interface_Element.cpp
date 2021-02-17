//
// Created by constantin on 21/04/2020.
//

#include "Interface_Element.h"

Interface_Element::Interface_Element(SDL_Renderer *ren){
    std::cout<<"   //// Renderer referenced"<<'\n';
    std::cout<<"     //// Parent"<<'\n';
    renderer=ren;

}

Interface_Element::~Interface_Element(){

}

void Interface_Element::setPos(const int &x, const int &y) {
    posX=x;
    posY=y;
}

void Interface_Element::draw() {}
void Interface_Element::update() {}