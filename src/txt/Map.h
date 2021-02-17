/**
* @brief Module gérant la map, ainsi que leurs fonction associées.
*
* La Map correspond au monde ou les joueurs peuvent interagir.
* @file Map.h
* @date 2020/04/28
* */
#ifndef CBFIGHTERS_MAP_H
#define CBFIGHTERS_MAP_H

#include "../core/Player.h"
#include <iostream>


class Map {
    /**
 * @brief La classe Map contient les dimensions de la map et un tableau 2D de caractères.
* */
private:
    int dimX;
    int dimY;
    char map [100][100];

public:
    /**
     * @brief Construit la Map
     * */
    Map();
    /**
     * @brief Fonction qui vérifie si une position est valide
     * @param x : entier
     * @param y : entier
     * */
    bool isValidePosition(const int x, const int y) const;
    /**
     * @brief Accesseur sur un élément de la carte
     * @param x : entier
     * @param y : entier
     * */
    char getElementHere(const int x, const int y) const;
    /**
     * @brief Mutateur sur un élément de la carte
     * @param x : entier
     * @param y : entier
     * */
    void setElementHere(const int x, const int y, const char element);
    /**
     * @brief Initialise la position des joueurs sur la carte.
     * @param p1 : un Player
     * @param p2 : un Player
     * */
    void initPlayerOnMap(Player &p1, Player &p2);
    /**
     * @brief place la position des joueurs sur la carte.
     * @param p1 : un Player
     * @param p2 : un Player
     * */
    void setPlayerOnMap(Player &p1, Player &p2);
    /**
     * @brief dessine la carte.
     * */
    void drawMap() const;
    /**
     * @brief accesseur sur DimX
     * */
    int getDimX() const;
    /**
     * @brief accesseur sur DimY
     * */
    int getDimY() const;
};


#endif //CBFIGHTERS_MAP_H