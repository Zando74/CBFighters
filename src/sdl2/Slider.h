//
// Created by constantin on 21/04/2020.
//

#ifndef CBFIGHTERS_SLIDER_H
#define CBFIGHTERS_SLIDER_H

#include "Interface_Element.h"
#include "BoxArea.h"
#include <iostream>
#include "../core/Player.h"

class Slider : public Interface_Element{
    /**
     * @brief La classe Slider permet l'affichage d'une barre de progression, utiliser lors de l'affichage des points de vie
     * Elle possède une réference au Player
     * 2 BoxArea, l'une affichant le fond et l'autre le remplissage de la barre
     * Un bool pour le sens de remplisage de la barre (gauche a droite ou droite a gauche)
     */
public:
    Player * anchorPlayer;
    BoxArea * bar;
    BoxArea * fill;
    bool bIsReversed;
    bool bIsActive;

    /**
     * @brief Constructeur de la classe
     * @param ren : le renderer
     * @param anchor : La référence au Player
     * @param reversed : le sens de remplissage
     */
    Slider(SDL_Renderer * ren, Player * anchor, bool reversed);

    /**
     * @brief Destructeur virtuel necessaire à l'utilisation de fonction virtuel
     */
    virtual ~Slider();

    /**
     * @brief Mutateur de la taille d'affichage du Slider
     * @param w : la largeur
     * @param h : la hauteur
     */
    void setSize(const int &w, const int&h);

    /**
     * @brief Fonction virtuel permettant la mise a jour des donnée du Slider
     * A chaque appel les points de vie du player sont récuperer
     */
    virtual void update();

    /**
     * @brief Fonction virtuel permettant l'affichage des deux BoxArea de Slider
     */
    virtual void draw();
};


#endif //CBFIGHTERS_SLIDER_H
