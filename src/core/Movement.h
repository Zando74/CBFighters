/**
* @brief Module gérant les mouvements des personnages, ainsi que leurs fonction associées.
*
* Un mouvement correspond au animations lors du deplacement d'un joueur, en effet ces données
* nous servirons à afficher des images afin d'animer le déplacement.
* @file Movement.h
* @date 2020/04/28
* */ 

#ifndef CBFIGHTERS_MOVEMENT_H
#define CBFIGHTERS_MOVEMENT_H

#include <iostream>
#include <list>
#include <string>


struct movementAction {
    /**
    * @brief structure de donnée associant a un caractère le nombre de fois
    * qu'il est répété.
    * */
    char img;
    int frames;
};

class Movement {
    /**
     * @brief La classe Movement contient une liste de movementAction, une copie de celle-ci,
     * ainsi que des variables utiles pour compter et savoir quel mouvement est ou doit etre joué.
     * */
public:
    /**
     * @brief Construit un Movement a partir de deux chaine de caractères.
     * @param fighterName : chaine de caractère correspondant au nom du fighter.
     * @param movementName : chaine de caractère correspondant au nom du mouvement.
     * */
    Movement(std::string & fighterName,std::string & movementName);
    /**
     * @brief Detruit l'objet Movement.
     * */
    ~Movement();

    /**
     * @brief Démarre un mouvement.
     * @param bodyFighter : un caractère, celui du Fighter
     * */
    void start(const char &bodyFighter);
    /**
     * @brief Actualise un mouvement si un mouvement à été démarré.
     * @param bodyFighter : un caractère, celui du Fighter. 
     * */
    void update(char &bodyFighter);
    /**
     * @brief Accesseur sur Started, un booléen vrai si un mouvement est joué.
     * */
    bool getStarted() const;
    /**
     * @brief Accesseur sur Finished, un booléen vrai si un mouvement n'est pas joué.
     * */
    bool getFinished() const;
    /**
     * @brief Mutateur sur Started, un booléen vrai si un mouvement est joué.
     * */
    void setStarted(bool b);
    /**
     * @brief Mutateur sur Finished, un booléen vrai si un mouvement n'est pas joué.
     * */
    void setFinished(bool b);
    /**
     * @brief Fonction de test du module Movement.
     * */
    void testRegression();

private:

    std::list<movementAction> list, cpList;

    int nbFrames;

    int cpt, cptMovement;
    int currentList;
    bool Started;
    bool Finished;

    char previousBody;
    /**
     * @brief Joue un mouvement, à partir de la liste de MovementAction
     * @param bodyFighter : Un caractère, celui du Fighter.
     * */
    void play(char &bodyFighter);

};


#endif //CBFIGHTERS_MOVEMENT_H
