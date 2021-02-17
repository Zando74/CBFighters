/**
* @brief Module gérant les boxes de collisions, ainsi que leurs fonction associées.
*
* Une BoxColliders contient différente type de boxes, associés a chaque images delimitant
* les zones ou l'on peut subir des coups, ou en infliger, ainsi que les collisions avec l'environnement.
* @file Boxcolliders.h
* @date 2020/04/28
* */
#ifndef CBFIGHTERS_BOXCOLLIDERS_H
#define CBFIGHTERS_BOXCOLLIDERS_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../core/Player.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

enum corners{
    /**
     * @brief Enumeration facilitant l'utilisation des index de tableau de pos
     * dans le cadre des tests des collisions
     * t : haut
     * b : bas
     * l : gauche
     * r : droit
     */
    tl=0,
    tr,
    bl,
    br
};

struct pos{
    /**
     * @brief La structure de donnée pos permet une utilisation plus simple
     * des positions dans le cadre des test de collisions
     */
    int x,y;
    /**
     * @brief Mutateur des positions de la structure pos
     * @param x : la position X a modifier
     * @param y : la position Y a modifier
     */
    void setPos(const int &x, const int & y);
};

struct Box{
    /**
     * @brief La structure de donnée box contient un rectangle SDL,
     * et un caractère pour indiquer sa couleur.
     * */
    SDL_Rect b;
    char couleur;
    /**
     * @brief Permet d'obtenir un tableau contenant les positions des 4 coins d'une Box
     * @return un tableau de taille 4 avec la position des coins
     */
    pos * getCorners();
    /**
     * @brief Permet d'obtenir un tableau contenant les positions relative a un joueur des 4 coins d'une Box
     * @param p : un Player
     * @return un tableau de taille 4 avec la position des coins
     */
    pos * getCorners(Player &p);
    /**
     * @brief Test de Collision
     * @param b
     * @param selfPlayer : le Player actuel
     * @param targetPlayer : le Player adverse
     * @return Vrai si un coin de la box du player est a l'interieur de la Box de l'adversaire
     */
    bool isInsideBox(Box &b,Player & selfPlayer , Player & targetPlayer);
    /**
     * @brief Test de Collision
     * @param b
     * @param selfPlayer : le Player actuel
     * @param targetPlayer : le Player adverse
     * @return Vrai si un coin de la box du player est autour de la Box de l'adversaire
     */
    bool isAroundBox(Box &b,Player & selfPlayer , Player & targetPlayer);
};

class Boxcolliders{
    /**
     * @brief La classe Boxcolliders contient un renderer pour indiquer a la SDL quoi afficher,
     * un tableau dynamique 2D de box contenant toutes les boxes associés a chaque frame, 
     * et un tableau Dynamique de box contenant les boxes de la frame actuel.
     * */
private:
    SDL_Renderer *renderer;
    vector<vector<Box>> collisionBox;
    vector<Box> currentBoxes;
    Player * playerRef;
    int collideSeed;

public:
    /**
     * @brief Constuit l'objet BoxColliders.
     * @param ren : un renderer en SDL.
     * @param player : un Player.
     * @param fighterName : une chaine de caractère.
     * @param moveName : une chaine de caractère.
     * @param side : un caractère.
     * */
    Boxcolliders(SDL_Renderer *ren,Player &player, string fighterName, string moveName, char side);
    /**
     * @brief Detruit l'objet BoxColliders.
     * */
    ~Boxcolliders();
    /**
     * @brief dessine un rectangle.
     * @param player : un Player.
     * */
    void drawRect(Player &player);
    /**
     * @brief actualise le tableau de boxe actuel.
     * @param player : un player.
     * */
    void update(Player &player);
    /**
     * @brief Fonction de test qui affiche le contenue des boxes.
     * @param indice : un entier.
     * */
    void testPrintBox(int indice);
    /**
     * @brief Choisit la bonne box en fonction du caractère du bodyFighter.
     * @param body : un caractère.
     * */
    void chooseCurrentBox(char body);
    /**
     * @brief accesseur sur un tableau dynamique de box parmis le tableau 2D
     * @param indice : un entier.
     * */
    vector<Box> getBoxes(int indice);
    /**
     * @brief vide les tableaux
     * */
    void clear();
    //void loadBoxFromFile(SDL_Renderer *ren,Player &player, string fighterName, string moveName);
    bool isColliding(Boxcolliders & target);
};

#endif //CBFIGHTERS_BOXCOLLIDERS_H
