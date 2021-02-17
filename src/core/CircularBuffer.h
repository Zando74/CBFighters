/**
@brief Module gérant Nos Pile circulaire, ainsi que ses fonctions associées.

 Une pile circulaire dans l'application est implementé par tableau Dynamique,
 sa taille definie par BUFFER_SIZE, si la pile est pleine l'élément le plus ancien
 est retiré et nos éléments se décalle d'une position en arriere pour liberer une place.
 @file CircularBuffer.h
 @date 2020/04/16
 */


#ifndef CBFIGHTERS_CIRCULARBUFFER_H
#define CBFIGHTERS_CIRCULARBUFFER_H



#include <vector>
#include "Moves.h"
class CircularBuffer {
/**
 * @brief La classe CircularBuffer contient nos 2 piles circulaires associées à chaque joueur,
 * Ces dernieres sont composées de tableau dynamique d'une capacité maximal de 3 éléments. 
* */
private:
    unsigned int BUFFER_SIZE;
    std::vector<char> frameBuffer1;
    std::vector<char> frameBuffer2;
    std::vector<std::vector<char>> buffer1;
    std::vector<std::vector<char>> buffer2;

public:
    /**
    * @brief Construit l'objet CircularBuffer.
    * Le constructeur initialise BUFFER_SIZE à 10, prérempli les frameBuffer à 3 caractere espace,
    * et prérempli nos piles Circulaires de frameBuffer.
    */
    CircularBuffer();
    /**
    * @brief Détruit l'objet CircularBuffer.
    */
    ~CircularBuffer();
    /**
    * @brief ajoute au frameBuffer de l'un des joueurs input.
    * @param input : caractère pressé au clavier.
    */
    void addInput(char input);
    /**
    * @brief vérifie que les piles circulaires ne sont pas pleine.
    * Si l'une des piles est pleine retire l'élément le plus ancien,
    * et décalle d'un rang en arriere nos éléments pour liberer une place.
    */
    void removeOldest();
    /**
    * @brief ajoute au piles circulaire, le tableau dynamique associés
    * appelle a removeOldest() pour verifié qu'il n'est pas plein
    * remise au caractere "neutre" les éléments de nos tableaux dynamique.
    */
    void addBuffer();
    /**
    * @brief copies le contenu d'une pile circulaire d'un de nos joueurs dans un tableau dynamique associé a ce joueur.
    * who permet d'identifié le joueur en question.
    * @param inputList : Tableau dynamique de Tableau dynamique de caractere.
    * @param who : un caractère
    */
    void saveToList(std::vector<std::vector<char>> &inputList,char who);
    /**
    * @brief fonction de test affichant le contenues des tableaux dynamiques
    */
    void testPrintbuffer();
    /**
    * @brief fonction de test affichant le contenues des piles circulaires.
    */
    void testPrintBufferGlobal();
    /**
    * @brief fonction effectuant le test de regression du module CircularBuffer.
    * genere un caractère aléatoire parmis la table ASCII essaye de l'ajouter aux tableaux dynamiques,
    * ajoutes les tableaux dynamiques aux piles circulaire, copie les piles, et tout ça  100 000 fois.
    */
    void testRegression();
};


#endif //CBFIGHTERS_CIRCULARBUFFER_H

