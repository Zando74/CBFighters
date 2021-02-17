#include "Map.h"
#include "../core/Player.h"

const char firstMap[9][47] = {
        "##############################################",
        "#............................................#",
        "#............................................#",
        "#............................................#",
        "#............................................#",
        "#............................................#",
        "#............................................#",
        "#............................................#",
        "##############################################"
};

Map::Map() {
    dimX = 46;
    dimY = 9;
    for(int x=0;x<dimX;x++)
        for(int y=0;y<dimY;y++)
            map[x][y] = firstMap[dimY-1-y][x];
}

bool Map::isValidePosition(const int x, const int y) const {
    return ((x>=0)&&(x<dimX)&&(y>=0)&&(y<=dimY)&&(map[x][y]!='#'));
}

char Map::getElementHere(const int x, const int y) const {
    return map[x][y];
}

void Map::setElementHere(const int x, const int y, const char element) {
    if(isValidePosition(x,y)){
        map[x][y] = element;
    }
}

void Map::initPlayerOnMap(Player &p1, Player &p2) {
    p1.setPositionX(20); p1.setPositionY(7);
    setElementHere(20,7,p1.getBodyFighter());
    p2.setPositionX(26); p2.setPositionY(7);
    setElementHere(26,7,p2.getBodyFighter());
}

void Map::setPlayerOnMap(Player &p1, Player &p2)
{
    setElementHere(p1.getPositionX(),p1.getPositionY(),p1.getBodyFighter());
    setElementHere(p2.getPositionX(),p2.getPositionY(),p2.getBodyFighter());
}

void Map::drawMap() const {
    for(int i=0;i<dimY;i++){
        for(int j=0;j<dimX;j++){
            std::cout << map[j][i];
        }
        std::cout << std::endl;
    }
}

int Map::getDimX() const {
    return dimX;
}

int Map::getDimY() const {
    return dimY;
}

