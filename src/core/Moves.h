/**
* @brief Module gérant les coups des personnages, ainsi que leurs fonction associées.
*
* Un coups correspond au animations lors du lancement d'un coup par un joueur, en effet ces données
* nous servirons à afficher des images afin d'animer le coup.
* @file Moves.h
* @date 2020/04/28
* */ 

#ifndef CBFIGHTERS_MOVES_H
#define CBFIGHTERS_MOVES_H

#include <iostream>
#include <list>
#include <string>

struct action {
    /**
    * @brief structure de donnée associant a un caractère le nombre de fois
    * qu'il est répété.
    * */
    char img;
    int frames;
};

class Moves {
    /**
     * @brief La classe Moves contient trois liste d'action, une copie de celle-ci,
     * ainsi que des variables utiles pour compter et savoir quel coup est ou doit etre joué.
     * et à quelle état le coup est actuellement.
     * */
public:
    /**
     * @brief Construit un Moves a partir de deux chaine de caractères.
     * @param fighterName : chaine de caractère correspondant au nom du fighter.
     * @param movementName : chaine de caractère correspondant au nom du moves.
     * */
    Moves(std::string & fighterName,std::string & moveName);
    /**
     * @brief Detruit l'objet Movement.
     * */
    ~Moves();
    /**
     * @brief Démarre un coup.
     * @param bodyFighter : un caractère, celui du Fighter
     * */
    void start(const char &bodyFighter);
    /**
     * @brief Actualise un coup si un coup à été démarré.
     * @param bodyFighter : un caractère, celui du Fighter. 
     * */
    void updateMove(char &bodyFighter);
    /**
     * @brief Accesseur sur Started, un booléen vrai si un coup est joué.
     * */
    bool getStarted() const;
    /**
     * @brief Accesseur sur Finished, un booléen vrai si un coup n'est pas joué.
     * */
    bool getFinished() const;
    /**
     * @brief Mutateur sur Started, un booléen vrai si un coup est joué.
     * */
    void setStarted(bool b);
    /**
     * @brief Mutateur sur Finished, un booléen vrai si un coup n'est pas joué.
     * */
    void setFinished(bool b);
    /**
     * @brief Fonction de test du module Moves.
     * */
    void testRegression();

private:
    std::list<action> listStartup, cpListStartup;
    std::list<action> listActive, cpListActive;
    std::list<action> listRecovery, cpListRecovery;

    int nbStartup;
    int nbActive;
    int nbRecovery;

    int cpt, cptMove;
    int currentList;
    bool Started;
    bool Finished;

    char previousBody;
    /**
     * @brief Joue le startup d'un coup, moments ou le fighter prepare son coup.
     * @param bodyFighter : Un caractère, celui du Fighter.
     * */
    void playStartup(char &bodyFighter);
    /**
     * @brief Joue l'active d'un coup, moments ou le fighter donne son coup.
     * @param bodyFighter : Un caractère, celui du Fighter.
     * */
    void playActive(char &bodyFighter);
    /**
     * @brief Joue le recovery d'un coup, moments ou le fighter recupere de son coup.
     * @param bodyFighter : Un caractère, celui du Fighter.
     * */
    void playRecovery(char &bodyFighter);
    
};


#endif //CBFIGHTERS_MOVES_H
