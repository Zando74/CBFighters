/**
@brief Module gérant Nos combattants 
Un combattant est avant tout representé par son caractère et son nom, c'est a partir de ce caractère
associé a son nom que l'on determine ce qu'il fait.
 @file Fighters.h
 @date 2020/04/16
 */

#ifndef CBFIGHTERS_FIGHTERS_H
#define CBFIGHTERS_FIGHTERS_H
#include <vector>
#include <string>
#include "Moves.h"
#include "Movement.h"


class Fighters {
    /**
@brief La classe Fighters contient une chaine de caractère pour le nom, un caractère pour son corps,
un tableau dynamique de coup possible, et de mouvements qui lui sont propres.
*/
private:
    std::string fighterName;
    char body;
    std::vector<Moves> movelist;
    std::vector<Movement> movementList;

public:
    /**
    * @brief Construit l'objet Fighters à partir de son nom
    * grâce au nom on peut recuperer les données des bons fichiers pour initialiser nos listes
    * de coups et de mouvements disponible.
    */
    Fighters(std::string & name);
    /**
    * @brief Détruit l'objet Fighters
    */
    ~Fighters();
    /**
    * @brief Accesseur sur la donnée membre FighterName de la classe.
    */
    std::string getFighterName();
    /**
    * @brief Accesseur sur la donnée membre Body de la classe.
    */
    char &getBody();
    /**
    * @brief Mutateur sur la donnée membre Body de la classe.
    */
    void setBody(char & c);
    /**
    * @brief Accesseur sur la donnée membre Move de la classe.
    */
    Moves &getMove(const int & i);
    /**
    * @brief Accesseur sur la donnée membre Movement de la classe.
    */
    Movement &getMovement(const int & i);
    /**
    * @brief Test de regression deu module Fighers.
    * charge des coups et des déplacements aléatoirement.
    */
    void testRegression();
};




#endif //CBFIGHTERS_FIGHTERS_H