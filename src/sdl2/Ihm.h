#ifndef CBFIGHTERS_IHM_H
#define CBFIGHTERS_IHM_H

#include <SDL2/SDL.h>
//#include <SDL_ttf.h>
//#include <SDL_image.h>
//#include <SDL_mixer.h>
#include <iostream>
#include "../core/Player.h"
#include "../core/Timer.h"
#include "../txt/Map.h"
#include "../txt/Input.h"
#include "../core/CircularBuffer.h"
#include "SpriteManager.h"
#include "Interface.h"
#include "Boxcolliders.h"

class Ihm {

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    //TTF_Font *font;
    //SDL_Color fontColor;
    Interface * UI;

    Boxcolliders *box1;
    Boxcolliders *box2;
    Timer t;
    CircularBuffer buffer;
    Player *p1;
    int p1Wins;
    int p2Wins;
    Player *p2;
    SpriteManager *p1Sprite;
    SpriteManager *p2Sprite;
    SpriteManager *map;
    TextArea * StartText;
    TextArea * titleText;
    TextArea * p1Score;
    TextArea * p2Score;
    Slider * HPP1;
    Slider * HPP2;

    double gameTimer;

    bool isRun;
    bool bisInMenu;

public:
    Ihm();
    ~Ihm();
    void collisionTest();
    void initPlayers();
    void updateEntity(Player &p,const int otherPlayerPosX, char who, char size,Player & otherPlayer);
    void update();
    void draw();
    void run();
    void resetRound();
    void verifyWinCond(bool timeUp);
};


#endif //CBFIGHTERS_IHM_H