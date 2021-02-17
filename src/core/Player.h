/**
* @brief Module gérant le joueur, ainsi que leurs fonction associées.
*
* Un Player correspond à l'entité controllé par le joueur, il rassemble en partie
* tous les autres modules servant lors d'un combat.
* @file Player.h
* @date 2020/04/28
* */

#ifndef CBFIGHTERS_PLAYER_H
#define CBFIGHTERS_PLAYER_H

#include "Position.h"
#include "Fighters.h"
#include "Timer.h"
#include "Health.h"
#include <string>
#include <iostream>
#include <vector>


class Player {
    /**
     * @brief La classe Player contient un pointeurs sur un Fighter, une chaine de caractère indiquant l'état actuel du Fighter.
     * ainsi qu'une Position, et un tableau 2D d'inputs contenant les entrée claviers du joueur.
     * */
private:
    Fighters *myFighter;
    std::string playerState;
    Position myPosition;

    int blockStun;
    int hitStun;
    int positionOnMap;
    std::vector<std::vector<char>> inputs;

public:
    Health myHealth;
    /**
     * @brief Construit le Player a partir d'un nom de Fighter et de coordonnées.
     * @param fighterName : chaine de caractère, le nom du Fighter.
     * @param x : un entier.
     * @param y : un entier.
     * */
    Player(std::string &fighterName, int x, int y);
    /**
     * @brief Detruit l'objet Player.
     * */
    ~Player();
    /**
     * @brief lance un coup à partir d'un indice.
     * @param indice : un entier, indiquant quel coup joué.
     * */
    void playMoves(int indice);
    /**
     * @brief actualise un coup à partir d'un indice.
     * @param indice : un entier, indiquant quel coup doit être actualisé.
     * */
    void updateMove(int indice);
    /**
     * @brief lance un mouvement à partir d'un indice.
     * @param indice : un entier, indiquant quel mouvement est joué.
     * */
    void playMovement(int indice);
    /**
     * @brief actualise un mouvement à partir d'un indice.
     * @param indice : un entier, indiquant quel mouvement doit être actualisé.
     * */
    void updateMovement(int indice);
    /**
     * @brief Accesseur sur BodyFighter du Fighter.
     * */
    char &getBodyFighter() const;
    /**
     * @brief Accesseur sur le PlayerState.
     * */
    std::string getPlayerState();
    /**
     * @brief Mutateur sur le PlayerState.
     * @param state : chaine de caractère.
     * */
    void setPlayerState(std::string state);
    /**
     * @brief Accesseur sur la position x.
     * */
    int getPositionX();
    /**
     * @brief Accesseur sur la position y.
     * */
    int getPositionY();
    /**
     * @brief Accesseur sur la position.
     * */
    Position & getPosition();
    /**
     * @brief Mutateur sur la position x.
     * @param pX : un entier.
     * */
    void setPositionX(const int pX);
    /**
     * @brief Mutateur sur la position y.
     * @param pY : un entier.
     * */
    void setPositionY(const int pY);
    /**
     * @brief Accesseur sur le tableau 2D d'inputs.
     * */
    const std::vector<std::vector<char>>& getInputs();
    /**
     * @brief Mutateur sur le tableau 2D d'inputs.
     * */
    std::vector<std::vector<char>>& setInputs();
    /**
     * @brief Fonction de test affichant les Inputs.
     * */
    void testPrintInputs();
    /**
     * @brief Fonction vérifiant les entrées permettant de joué le bon mouvement ou coup.
     * @param otherPlayerPosX : un entier, position x de l'autre joueur.
     * */
    void checkInput(int otherPlayerPosX);
    /**
     * @brief Accesseur sur le Fighter.
     * */
    Fighters & getMyFighter() const;
    bool getMoving();
    void setMoving(bool b);
    /**
     * @brief Accesseur sur la position du Joueur relative a la map.
     * */
    int getPositionOnMap();
    /**
     * @brief Mutateur sur la position du Joueur relative a la map.
     * */
    void setPositionOnMap(int p);
    Health& getHealth();
    /**
     * @brief Fonction de test du module Player.
     * */
    void testRegression();

    int getBlockStun();

    void setBlockStun(int stun);

    void blockStunState(Player & otherPlayer);

    void hitStunState(Player & otherPlayer);

    void setHitStun(int stun);
};


#endif //CBFIGHTERS_PLAYER_H