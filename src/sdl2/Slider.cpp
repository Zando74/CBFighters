//
// Created by constantin on 21/04/2020.
//

#include "Slider.h"

Slider::Slider(SDL_Renderer * ren, Player * anchor,bool reversed) :
    Interface_Element(ren),
    anchorPlayer(anchor)
    {
    std::cout<<"////////////// INITIALIZED TEST HP BAR"<<"\n";
    bar= new BoxArea(renderer);
    fill = new BoxArea(renderer);
    bIsReversed = reversed;
    bIsActive = true;
    fill->setColor(255);


    if(bIsReversed){
        setPos(384-160,10);
    }else{
        setPos(10,10); //384 224
    }
    bar->setDrawPos(posX, posY);
    fill->setDrawPos(posX,posY);
    bar->setSize(150,20);
    fill->setSize(150,20);

    if(bIsReversed){
        fill->DrawBox.x=384-10;
        fill->DrawBox.y=posY;
        fill->DrawBox.w=-fill->DrawBox.w;
    }
}

Slider::~Slider() {
    delete bar;
    delete fill;
}

void Slider::setSize(const int &w, const int&h) {
    bar->setSize(w,h);
    fill->setSize(w/2,h);
}

void Slider::update() {
    if(bIsReversed){
        fill->DrawBox.w = -anchorPlayer->getHealth().getCurrent();
    } else fill->DrawBox.w = anchorPlayer->getHealth().getCurrent();
}


void Slider::draw() {
    //std::cout<<"  DRAW TEST HP BAR : "<<this<<"\n";
    if(bIsActive) {
        bar->drawBox();
        fill->drawBox();
    }
}