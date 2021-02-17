/**
* @brief Module gérant les entrée clavier en mode texte, ainsi que leurs fonction associées.
*
* Input ecoute et sauvegarde les entrées claviers.
* @file Input.h
* @date 2020/04/28
* */
#ifndef CBFIGHTERS_INPUT_H
#define CBFIGHTERS_INPUT_H

#include <string>
#include <iostream>

class Input {
    /**
     * @brief La classe Input contient un caractère lu au clavier.
     * */
private:
    char input;
public:
    /**
     * @brief Construit l'objet Input
     * */
    Input();
    /**
     * @brief Detruit l'objet Input
     * */
    ~Input();
    /**
     * @brief accesseur sur Input
     * */
    char getInput();
    /**
     * @brief ecoute les entrées clavier
     * */
    void listenInput();
};


#endif //CBFIGHTERS_INPUT_H