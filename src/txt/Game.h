/**
* @brief Module gérant le jeu en mode texte, ainsi que leurs fonction associées.
*
* Game correspond à l'entité controllé par le joueur, il rassemble en partie
* tous les autres modules servant lors d'un combat.
* @file Game.h
* @date 2020/04/28
* */
#ifndef CBFIGHTERS_GAME_H
#define CBFIGHTERS_GAME_H

#include <iostream>
#include <string>
#include "../core/Player.h"
#include "../core/Timer.h"
#include "Map.h"
#include "Input.h"
#include "../core/CircularBuffer.h"

class Game {
    /**
 * @brief La classe Game contient un Timer pour l'actualisation à 60fps,
 * une map, un CircularBuffer, un Input, 2 joueurs et 
* */
private:
    Timer t;
    Map world;
    CircularBuffer buffer;
    Input hear;
    Player *p1;
    Player *p2;
    bool isRun;
public:
    /**
     * @brief Construit l'ojet Game
     * @param nameFighter1 : nom du premier Fighter.
     * @param nameFighter2 : nom du deuxieme Fighter.
     * */
    Game(string& nameFighter1, string& nameFighter2);
    /**
     * @brief Detruit l'objet Game
     * */
    ~Game();
    /**
     * @brief Deplace les joueurs
     * */
    void moveEntity();
    /**
     * @brief actualise le jeu.
     * */
    void update();
    /**
     * @brief dessine le jeu.
     * */
    void draw();
    /**
     * @brief lance le jeu.
     * */
    void run();
};

#endif //CBFIGHTERS_INPUT_H