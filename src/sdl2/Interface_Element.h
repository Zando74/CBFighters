//
// Created by constantin on 21/04/2020.
//

#ifndef CBFIGHTERS_INTERFACE_ELEMENT_H
#define CBFIGHTERS_INTERFACE_ELEMENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>


class Interface_Element {
    /**
     * @brief La classe Interface_Element est la classe père dont tout les élément d'interface vont hériter.
     * Elle contient une référence au renderer et des positions
     */
public:
    SDL_Rect I;

    /**
     * @brief Constructeur de la classe
     * @param ren : pointeur vers le renderer
     */
    Interface_Element(SDL_Renderer * ren);
    /**
     * @brief Destructeur virtuel necessaire a l'utilisation de fonction virtuels
     */
    virtual ~Interface_Element();

    /**
     * @brief Mutateur des positions
     * @param x : Position X à modifier
     * @param y : Posititon Y à modifier
     */
    void setPos(const int &x, const int &y);

    /**
     * @brief Fonction virtuel permettant la mise a jour des données
     */
    virtual void update();

    /**
     * @brief Fonction virtuel permettant l'affichage
     */
    virtual void draw();

protected:

    SDL_Renderer * renderer;
    int posX;
    int posY;
};


#endif //CBFIGHTERS_INTERFACE_ELEMENT_H
