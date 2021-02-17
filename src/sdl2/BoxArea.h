//
// Created by constantin on 24/04/2020.
//

#ifndef CBFIGHTERS_BOXAREA_H
#define CBFIGHTERS_BOXAREA_H

#include "Interface_Element.h"
#include "Box_Interface.h"

class BoxArea : public Box_Interface{
    /**
     * @brief est une simplification de Box_Interface, pour une utilisation plus naturelle des SDL_Rect dans le cadre de l'interface
     */
public:
    /**
     * @brief Constructeur de la classe
     * @param ren : le renderer
     */
    BoxArea(SDL_Renderer * ren);
    /**
     * @brief Destructeur de la classe
     */
    ~BoxArea();

    /**
     * @brief Override de l'affichage de Box_Interface
     */
    void drawBox() override;

};


#endif //CBFIGHTERS_BOXAREA_H
