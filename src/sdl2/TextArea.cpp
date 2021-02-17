//
// Created by constantin on 24/04/2020.
//

#include "TextArea.h"

TextArea::TextArea(SDL_Renderer * ren, const int & x, const int & y) : Interface_Element(ren){
    std::cout<<"////////////// INITIALIZED TEXT AREA"<<'\n';
    text = new std::string("SAMPLE") ;
    textBox = new BoxArea(ren);
    background = new BoxArea(ren);
    background->setColor();
    bShowBG= false;

    setTextPos(x,y);
    //
}

TextArea::~TextArea(){
    delete textBox;
    delete background;
    delete text;
}

void TextArea::setText(const char newtext[]){
    delete text;
    text = new std::string(newtext);
}

void TextArea::setTextSize(const int & w, const int & h){

    if(textBox->DrawBox.w != 20)
        setTextPos(textBox->DrawBox.x + (textBox->DrawBox.w/2),textBox->DrawBox.y);
    textBox->setSize(w,h);
    background->setSize(w,h);

    setTextPos(textBox->DrawBox.x -(w/2),textBox->DrawBox.y);
}

void TextArea::update(){

    TTF_Font* Sans = TTF_OpenFont("data/font/OpenSans-Regular.ttf", 16); //this opens a font style and sets a size
    //std::cout<<TTF_GetError()<<'\n';
    SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

    char print[text->size()+1] ;
    strcpy(print, text->c_str());
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, print, White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
    Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture




    //Don't forget to free your surface and texture
    SDL_FreeSurface(surfaceMessage);
    TTF_CloseFont(Sans);
}


void TextArea::draw(){
    //std::cout<<"  DRAW TEXT AREA"<<"\n";
    if(bShowBG){
        background->drawBox();
    }
    SDL_RenderCopy(renderer, Message, NULL, &textBox->DrawBox); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
    SDL_DestroyTexture(Message);


}

void TextArea::setTextPos(const int & x, const int & y){
    textBox->setDrawPos(x,y);
    background->setDrawPos(x,y);
}