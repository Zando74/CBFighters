/**
@brief Module gérant l'actualisation du programme, ainsi que ses fonctions associées.

 @file Timer.h
 @date 2020/04/16
 */

#ifndef CBFIGHTERS_TIMER_H
#define CBFIGHTERS_TIMER_H

#include <chrono>
#include <cstdint>

using namespace std;
using namespace chrono;

using frame = duration<int32_t, ratio<1, 60>>;
using ms = duration<float, milli>;


class Timer {
/**
@brief La classe Timer reutilise les fonctionalité du module Chrono de la bibliothèque standard
dans le but de permettre une actualisation à 60 actualisation par secondes. 
*/
private:
    time_point<steady_clock> fpsTimer;
    frame FPS{};
    void updateFrame();


public:
    /**
    * @brief Construit l'objet Timer.
    * le constructeur initialise fpsTimer aux temps actuel.
    */
    Timer();
    /**
    * @brief detruit l'objet Timer.
    */
    ~Timer();
    /**
    * @brief cette fonction est vrai seulement si il c'est écoulé environ 16millisecondes.
    */
    bool isOK();
    /**
    * @brief Fonction de test qui affiche a chaque frame le temps depuis la frame precedente durant 3sec.
    */
    void countFrameIn3Sec();
    /**
    * @brief Construit l'objet Timer.
    * le constructeur initialise fpsTimer aux temps actuel.
    */
    void testRegression();

};


#endif //CBFIGHTERS_TIMER_H
