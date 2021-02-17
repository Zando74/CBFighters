//
// Created by constantin on 21/04/2020.
//

#ifndef CBFIGHTERS_HEALTH_H
#define CBFIGHTERS_HEALTH_H


class Health {
    /**
     * @brief La classe Health Permet la gestion des points de vie d'un Player
     */
public:
    /**
     * @brief Constructeur de la classe
     */
    Health();

    /**
     * @brief de la classe
     */
    ~Health();

    /**
     * @brief Accesseur des points de vie actuel
     * @return le nombre de points de vie actuel
     */
    int getCurrent();

    /**
     * @brief Permet d'infliger des dégats
     * @param dmg : nombre de dégats
     * @param seed : (inutilisé) empeche de prendre plusieurs fois des dégats de la meme source
     */
    void takeDamage(int dmg, int seed);

private:
    int Current;
    int Max;
};


#endif //CBFIGHTERS_HEALTH_H
