//
// Created by constantin on 24/04/2020.
//

#include "BoxArea.h"

BoxArea::BoxArea(SDL_Renderer *ren) : Box_Interface(ren){
    std::cout<<"       //// BoxArea"<<"\n";

}

BoxArea::~BoxArea(){}

void BoxArea::drawBox(){
    //std::cout<<"    BOX AT "<< DrawBox.x<<" / " << DrawBox.y<<'\n';
    SDL_SetRenderDrawColor(renderer, R, G, B, 255);
    SDL_RenderFillRect(renderer, &DrawBox);
    SDL_RenderDrawRect(renderer, &DrawBox);
}