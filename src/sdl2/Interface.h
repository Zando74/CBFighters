//
// Created by constantin on 21/04/2020.
//

#ifndef CBFIGHTERS_INTERFACE_H
#define CBFIGHTERS_INTERFACE_H

#include "InterfaceGeneral.h"
#include <iostream>
#include <vector>
#include <typeinfo>

class Interface {
    /**
     * @brief La classe Interface permet l'affichage de tout les objets héritant de Interface_Element
     * Elle possède un vecteur contenant tout les objets héritant de InterfaceElement voulant etre afficher
     */
public:
    std::vector<Interface_Element*> All_UI_Elem;

    /**
     * @brief Constructeur de la classe
     */
    Interface();
    Interface(std::vector<Interface_Element> AddVector);
    /**
     * Destructeur de la classe
     */
    ~Interface();

    /**
     * @brief appel l'update de tout les Interface_Element dans le vecteur
     */
    void update();
    /**
     * @brief appel le draw de tout les Interface_Element dans le vecteur
     */
    void draw();

    /**
     * Permet l'ajout d'un objet héritant de Interface_Element dans le vecteur
     * @param add : l'élement a ajouter
     */
    void addElem(Interface_Element * add);

};


#endif //CBFIGHTERS_INTERFACE_H
