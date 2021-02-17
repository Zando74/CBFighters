//
// Created by constantin on 24/04/2020.
//

#ifndef CBFIGHTERS_TEXTAREA_H
#define CBFIGHTERS_TEXTAREA_H

#include "Interface_Element.h"
#include "BoxArea.h"
#include <SDL2/SDL_ttf.h>
#include <string>

class TextArea : public Interface_Element{
    /**
     * @brief TextArea permet l'affichage de texte
     * Elle possède 2 BoxArea, une pour le texte, l'autre pour le fond, désactivable avec le bool bShowBG
     * Elle possède aussi un string pour le texte a afficher
     * et une texture pour traduire ce texte en image pour SDL
     */
public:
    BoxArea * textBox;
    BoxArea * background;
    SDL_Texture* Message;
    std::string * text;
    bool bShowBG;

    /**
     * @brief Constructeur de la classe
     * @param ren : le renderer
     * @param x : la position X
     * @param y : la position Y
     */
    TextArea(SDL_Renderer * ren, const int & x, const int & y);
    /**
     * @brief Destructeur de la classe
     */
    ~TextArea();
    /**
     * @brief Permet l'affichage
     */
    void draw() override;
    /**
     * @brief Met a jour les donnée de la classe TextArea
     */
    void update() override;
    /**
     * @brief Mutateur du texte a afficher
     * @param newtext : le nouveau texte
     */
    void setText(const char newtext[]);

    /**
     * @brief Mutateur de la taille des BoxArea de la classe
     * @param w : la largeur
     * @param h : la hauteur
     */
    void setTextSize(const int & w, const int & h);

    /**
     * @brief Mutateur des position d'affichage du texte
     * @param x : la position X
     * @param y : la position Y
     */
    void setTextPos(const int & x, const int & y);
};


#endif //CBFIGHTERS_TEXTAREA_H
