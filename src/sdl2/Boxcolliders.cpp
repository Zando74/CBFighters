#include <iostream>
//#include <SDL2/SDL.h>
#include "Boxcolliders.h"
#include "../core/Player.h"
#include <stdlib.h>
#include <string>


Boxcolliders::Boxcolliders(SDL_Renderer *ren,Player &player, string fighterName, string moveName, char side) {
    ifstream moveFile("data/characters/" + fighterName + "/" + moveName + "/cb" + moveName + side + ".txt");
    Box cp;
    playerRef = &player;
    collideSeed=rand()%1000;
    vector<Box> litleCollisionBox;
    int nbLitleCollisionBox;
    char testChange;
    if(moveFile.is_open()){
        moveFile >> nbLitleCollisionBox;
        while(nbLitleCollisionBox > 0){
            moveFile >> testChange;
            if(testChange != 't'){
                cp.couleur = testChange;
                moveFile >> cp.b.x >> cp.b.y >> cp.b.w >> cp.b.h;
                litleCollisionBox.push_back(cp);
            }else{
                collisionBox.push_back(litleCollisionBox);
                nbLitleCollisionBox--;
                litleCollisionBox.clear();
            }
        }
    }
    else{
        std::cout << "erreur durant l'ouverture du fichier data/characters/" << fighterName << "/" << moveName << "/" << moveName << ".txt" << std::endl;
        exit(EXIT_FAILURE);
    }
    moveFile.close();
    renderer = ren;
    for (unsigned int i = 0; i < collisionBox.size();i++){
        for(unsigned int j = 0; j< collisionBox[i].size();j++){
            //collisionBox[i][j].b.x += player.getPositionX();
            //collisionBox[i][j].b.y += player.getPositionY()-90;
        }
    }
    //allBoxcolliders.push_back(collisionBox);
}


Boxcolliders::~Boxcolliders(){
    collisionBox.clear();
}

void Boxcolliders::drawRect(Player &player) {
    for(unsigned int j = 0;j < currentBoxes.size();j++){
        if (currentBoxes[j].couleur == 'r'){
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        }
        if (currentBoxes[j].couleur == 'g'){
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        }
        if (currentBoxes[j].couleur == 'b'){
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        }
        //SDL_RenderFillRect(renderer, &collisionBox[i][j].b);
        SDL_Rect cpB = currentBoxes[j].b;
        cpB.x += player.getPositionX();
        cpB.y += player.getPositionY()-90;
        SDL_RenderDrawRect(renderer, &cpB);
    }
}

void Boxcolliders::update(Player &player){
    for(unsigned int i = 0; i < collisionBox[0].size();i++){
        //collisionBox[0][i].b.x = player.getPositionX();
        //collisionBox[0][i].b.y = player.getPositionY()-90;
    }
}

void Boxcolliders::testPrintBox(int indice){
    std::cout << "move frame" << indice <<" contient : " << std::endl;
    for(unsigned int j=0;j<collisionBox[indice].size();j++){
        std::cout << "[couleur :" << collisionBox[indice][j].couleur << ",posX : "<< collisionBox[indice][j].b.x << ",posY : "<< collisionBox[indice][j].b.y << "]";
    }
    std::cout << std::endl;
}


void Boxcolliders::chooseCurrentBox(char body){
    switch(body){
        case 'a':
            currentBoxes = getBoxes(0);
            //testPrintBox(0);
            break;
        case 'b':
            currentBoxes = getBoxes(1);
            //testPrintBox(1);
            break;
        case 'c':
            currentBoxes = getBoxes(2);
            //testPrintBox(2);
            break;
        case 'd':
            currentBoxes = getBoxes(3);
            //testPrintBox(3);
            break;
        case 'e':
            currentBoxes = getBoxes(4);
            //testPrintBox(4);
            break;
        case 'f':
            currentBoxes = getBoxes(5);
            //testPrintBox(5);
            break;
        case 'g':
            currentBoxes = getBoxes(6);
            //testPrintBox(6);
            break;
        default:
            break;
    }
}

vector<Box> Boxcolliders::getBoxes(int indice)
{

    return collisionBox[indice];
}

void Boxcolliders::clear()
{
    for(unsigned int i=0;i<collisionBox.size();i++){
        for(unsigned int j=0;j<collisionBox[i].size();j++){
            collisionBox[i].pop_back();
        }
        collisionBox[i].clear();
    }
    collisionBox.clear();
}

void pos::setPos(const int & _x, const int & _y){
    x=_x;
    y=_y;
}


pos * Box::getCorners(){
    pos * buff = new pos[4];
    buff[tl].setPos(this->b.x,this->b.y);
    buff[tr].setPos(this->b.x+this->b.w,this->b.y);
    buff[bl].setPos(this->b.x,this->b.y+this->b.h);
    buff[br].setPos(this->b.x+this->b.w,this->b.y+this->b.h);
    return buff;
}

pos * Box::getCorners(Player & p){
    pos * buff = new pos[4];
    buff[tl].setPos(this->b.x+p.getPositionX(),this->b.y+p.getPositionY()-90);
    buff[tr].setPos(this->b.x+this->b.w+p.getPositionX(),this->b.y+p.getPositionY()-90);
    buff[bl].setPos(this->b.x+p.getPositionX(),this->b.y+this->b.h+p.getPositionY()-90);
    buff[br].setPos(this->b.x+this->b.w+p.getPositionX(),this->b.y+this->b.h+p.getPositionY()-90);

    return buff;
}

bool Box::isAroundBox(Box & _b,Player & selfPlayer, Player & targetPlayer){
    pos * temp = this->getCorners(selfPlayer);
    pos * targetBox= _b.getCorners(targetPlayer);
    for (int index = 0; index < 4; ++index) {
        std::cout<<"/////////////////// "
            <<index<<" x "<<temp[tl].x <<"<"<< targetBox[index].x<< "<"<< temp[br].x<<'\n'
            <<"/////////////////// " <<index<<" y "<<temp[tl].y <<"<"<< targetBox[index].y<< "<"<< temp[br].y<<'\n';
        if(targetBox[index].x > temp[tl].x
            && targetBox[index].y > temp[tl].y
            && targetBox[index].x < temp[br].x
            && targetBox[index].y < temp[br].y){

            delete [] targetBox;
            delete [] temp;
            return true;
        }
    }
    delete [] targetBox;
    delete [] temp;
    std::cout<<"NO HIT"<<'\n';
    return false;
}

bool Box::isInsideBox(Box &b,Player & selfPlayer , Player & targetPlayer){
    if(b.isAroundBox(*this,targetPlayer, selfPlayer)){
        return true;
    }
    std::cout<<"ALSO NO HIT"<<'\n';
    return false;
}


bool Boxcolliders::isColliding(Boxcolliders & target){
    bool result =false;
    for (unsigned int index = 0; index < currentBoxes.size(); ++index) {

        pos * allCornersSelf= nullptr;
        if(currentBoxes[index].couleur == 'r') {
            allCornersSelf = currentBoxes[index].getCorners();
        }


        if(allCornersSelf != nullptr){
            for (unsigned int targetIndex = 0; targetIndex < target.currentBoxes.size(); ++targetIndex) {
                if(target.currentBoxes[targetIndex].couleur == 'b'){
                    if(!result){
                        result = currentBoxes[index].isAroundBox(target.currentBoxes[targetIndex], *playerRef, *target.playerRef);
                        if(!result){
                            result = currentBoxes[index].isInsideBox(target.currentBoxes[targetIndex], *playerRef, *target.playerRef);
                            //result = target.currentBoxes[targetIndex].isAroundBox(currentBoxes[index]);
                            if(result) break;
                        }
                    }
                }
            }
        }
        delete [] allCornersSelf;
    }

    if(result){
        std::string state = target.playerRef->getPlayerState();
        if((state == "st-bk")||(state == "cr-bk"))
        {
            target.playerRef->getHealth().takeDamage(1,0);
            target.playerRef->setBlockStun(11);
        }
        else
        {
            target.playerRef->getHealth().takeDamage(2,0);
            target.playerRef->setHitStun(11);
        }

    }
    return result;
}