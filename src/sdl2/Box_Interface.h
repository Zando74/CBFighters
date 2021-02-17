//
// Created by constantin on 24/04/2020.
//

#ifndef CBFIGHTERS_BOX_INTERFACE_H
#define CBFIGHTERS_BOX_INTERFACE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Interface_Element.h"

class Box_Interface : public Interface_Element{
    /**
     * @brief La classe Box_Interface Ajoute la posibilité d'afficher des SDL_Rect a une classe héritant de Interface_Element
     * Elle possède un SDL_Rect et une couleur RGB
     */
public:
    SDL_Rect DrawBox;
    /**
     * @brief Constructeur de la classe
     * @param ren : le renderer
     */
    Box_Interface(SDL_Renderer *ren);

    /**
     * @brief Destructeur virtuel necessaire a l'utilisation de fonction virtuel
     */
    virtual ~Box_Interface();

    /**
     * @brief Fonction virtuel pour l'affichage du SDL_Rect
     */
    virtual void drawBox();

    /**
     * @brief Mutateur des couleurs de la Box lors de l'affichage
     * @param r : Rouge
     * @param g : Vert
     * @param b : Bleu
     */
    void setColor(const int & r=0, const int & g=0,const int & b=0);

    /**
     * @brief Mutateur des position d'affichage du SDL_Rect
     * @param x : Position X a modifier
     * @param y : Position Y a modifier
     */
    void setDrawPos(const int & x=10, const int & y=10);

    /**
     * @brief Mutateur de la taille du SDL_Rect
     * @param w : Largeur a modifier
     * @param h : Hauteur a modifier
     */
    void setSize(const int & w=10, const int & h=10);

protected:
    int R,G,B;
};


#endif //CBFIGHTERS_BOX_INTERFACE_H
