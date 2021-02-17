#include "Ihm.h"
#include <SDL2/SDL.h>
//#include <SDL_ttf.h>
//#include <SDL_image.h>
//#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include "../txt/Game.h"
#include "SpriteManager.h"
#include "../core/Player.h"
#include "Boxcolliders.h"

Ihm::Ihm()
{
    isRun = true;
    bisInMenu=true;
    std::string p1Name("ryu");
    std::string p2Name("ryu");
    p1 = new Player(p1Name,152,200);
    p1Wins=0;
    p2 = new Player(p2Name,232,200);
    p2Wins=0;
    HPP1 = nullptr;
    HPP2 = nullptr;
    if(SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init()<0){
        std::cout << "Erreur d'initialisation" << SDL_GetError() << TTF_GetError()<< std::endl;
        SDL_Quit();
        exit(1);
    }
    window = SDL_CreateWindow("CBFighters", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,384,224,SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if(window == NULL){
        std::cout << "Erreur lors de la creation de la fenetre :" << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
    renderer = SDL_CreateRenderer(window,-1,0);
    if(renderer) {
        SDL_SetRenderDrawColor(renderer,255,255,255,255);

        std::cout<<"renderer cree"<<std::endl;
        std::cout<<"ici 1 ?";
        UI = new Interface();
        map = new SpriteManager(p1Name,renderer);
        p1Sprite = new SpriteManager(*p1,renderer);
        p2Sprite = new SpriteManager(*p2,renderer);
        box1 = new Boxcolliders(renderer, *p1, p1Name, "st", 'L');
        box2 = new Boxcolliders(renderer, *p1, p1Name, "st", 'R');

        titleText= new TextArea(renderer, 384/2, 10);
        StartText= new TextArea(renderer , 384/2, 90);
        titleText->bShowBG=true;
        titleText->setText("CBFIGHTERS");
        titleText->setTextSize(96,32);
        StartText->setText("START");
        StartText->setTextSize(50,20);


        UI->addElem(titleText);
        UI->addElem(StartText);
    }
}

Ihm::~Ihm()
{
    delete p1; p1 = nullptr;
    delete p2; p2 = nullptr;
    delete p1Sprite; p1Sprite = nullptr;
    delete  p2Sprite; p2Sprite = nullptr;
    delete  map; map = nullptr;
    delete  box1; box1 = nullptr;
    delete  box2; box2 = nullptr;
   // delete  box; box = nullptr;
    delete UI; UI= nullptr;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void Ihm::draw() {
    SDL_RenderClear(renderer);
    map->renderMap();
    if(!bisInMenu)
    {
        p1Sprite->renderSprite(*p1, p2->getPositionX());
        p2Sprite->renderSprite(*p2, p1->getPositionX());
        box1->drawRect(*p1);
        box2->drawRect(*p2);
    }
    UI->draw();
    SDL_RenderPresent(renderer);
    //box->testPrintBox();
}

void Ihm::update() {
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    SDL_PumpEvents();
    if(keyState[SDL_SCANCODE_ESCAPE])
        isRun = false;
    if(keyState[SDL_SCANCODE_RETURN]){
        if(bisInMenu){
            bisInMenu = false;
            StartText->setText(" ");
            titleText->setTextSize(40,30);
            titleText->setText("99");
            initPlayers();
            resetRound();
        }
    }
    if(!bisInMenu) {
        if (keyState[SDL_SCANCODE_W])
            buffer.addInput('z');
        if (keyState[SDL_SCANCODE_A])
            buffer.addInput('q');
        if (keyState[SDL_SCANCODE_S])
            buffer.addInput('s');
        if (keyState[SDL_SCANCODE_D])
            buffer.addInput('d');
        if (keyState[SDL_SCANCODE_U])
            buffer.addInput('u');
        if (keyState[SDL_SCANCODE_I])
            buffer.addInput('i');
        if (keyState[SDL_SCANCODE_O])
            buffer.addInput('o');
        if (keyState[SDL_SCANCODE_J])
            buffer.addInput('j');
        if (keyState[SDL_SCANCODE_K])
            buffer.addInput('k');
        if (keyState[SDL_SCANCODE_L])
            buffer.addInput('l');

        if (keyState[SDL_SCANCODE_UP])
            buffer.addInput('w');
        if (keyState[SDL_SCANCODE_LEFT])
            buffer.addInput('x');
        if (keyState[SDL_SCANCODE_DOWN])
            buffer.addInput('c');
        if (keyState[SDL_SCANCODE_RIGHT])
            buffer.addInput('v');
        if (keyState[SDL_SCANCODE_KP_7])
            buffer.addInput('7');
        if (keyState[SDL_SCANCODE_KP_8])
            buffer.addInput('8');
        if (keyState[SDL_SCANCODE_KP_9])
            buffer.addInput('9');
        if (keyState[SDL_SCANCODE_KP_4])
            buffer.addInput('4');
        if (keyState[SDL_SCANCODE_KP_5])
            buffer.addInput('5');
        if (keyState[SDL_SCANCODE_KP_6])
            buffer.addInput('6');
    }
    if(!bisInMenu)
    {
        collisionTest();
        int roundedTimer = gameTimer;
        std::string st= std::to_string(roundedTimer);
        char write[5];
        strcpy(write, st.c_str());
        titleText->setText(write);
        if(gameTimer>0){
            gameTimer-=0.0167;
            verifyWinCond(0);
        }
        else verifyWinCond(1);

    }
    UI->update();
}

void Ihm::initPlayers(){
    gameTimer =99;

    if(HPP1 == nullptr && HPP2 == nullptr){
        HPP1= new Slider(renderer,p1,0);
        HPP2= new Slider(renderer,p2,1);
        p1Score = new TextArea(renderer, 20,35);
        p2Score = new TextArea(renderer, 384-20,35);
        p1Score->setTextSize(20,20);
        p2Score->setTextSize(20,20);
        p1Score->setText("0");
        p2Score->setText("0");

        UI->addElem(HPP1);
        UI->addElem(HPP2);
        UI->addElem(p1Score);
        UI->addElem(p2Score);
    }
}

void Ihm::verifyWinCond(bool timeUp){
    if(p1->myHealth.getCurrent()==0){
        p2Wins++;
        resetRound();
    }

    if(p2->myHealth.getCurrent()==0){
        p1Wins++;
        resetRound();
    }

    if(timeUp){
        if(p1->myHealth.getCurrent()==p2->myHealth.getCurrent()){
            resetRound();
        }

        if(p1->myHealth.getCurrent()>p2->myHealth.getCurrent()){
            p1Wins++;
            resetRound();
        }
        else{
            p2Wins++;
            resetRound();
        }
    }

    if(p1Wins==2 || p2Wins ==2)
    {
        bisInMenu = true;
        titleText->setText("CBFIGHTERS");
        titleText->setTextSize(96,32);
        StartText->setText("START");
        StartText->setTextSize(50,20);
        HPP1->bIsActive=false;
        HPP2->bIsActive=false;
        p1Score->setText(" ");
        p2Score->setText(" ");
        p1Wins=0;
        p2Wins=0;

    }else{
        std::string st1= std::to_string(p1Wins);
        char writep1[5];
        strcpy(writep1, st1.c_str());
        p1Score->setText(writep1);

        std::string st2= std::to_string(p2Wins);
        char writep2[5];
        strcpy(writep2, st2.c_str());
        p2Score->setText(writep2);
    }
}

void Ihm::collisionTest(){
    std::cout<<"//Collision Test"<<'\n';
    box1->isColliding(*box2);
    box2->isColliding(*box1);
}

void Ihm::resetRound(){
    gameTimer=99;
    delete p1; delete p2; //delete map;
    std::string p1Name("ryu");
    std::string p2Name("ryu");
    //map = new SpriteManager(p1Name,renderer);
    p1 = new Player(p1Name,152,200);
    p2 = new Player(p2Name,232,200);
    //map->updateMap(*p1,*p2);
    HPP1->anchorPlayer= p1;
    HPP2->anchorPlayer= p2;
    HPP1->bIsActive=true;
    HPP2->bIsActive=true;
}

void Ihm::updateEntity(Player &p,const int otherPlayerPosX,char who,char side,Player & otherPlayer) {
    std::string cpyState = p.getPlayerState();
    char a = 'a';
    p.getMyFighter().setBody(a);
    if(cpyState == "st-lp"){
        if(!p.getMyFighter().getMove(0).getStarted()){
            p.playMoves(0);
            std::cout << "PLAY STANDING LIGHT PUNCH" << std::endl;
            if(who == '1'){
                box1->clear();
                delete box1;
                box1 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }else{
                box2->clear();
                delete box2;
                box2 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }
        }
        p.updateMove(0);
        if(p.getMyFighter().getMove(0).getFinished()) {
            p.setPlayerState("st");
            p.getMyFighter().getMove(0).setFinished(false);
            p.getMyFighter().getMove(0).setStarted(false);
            std::cout<< "ouheo" << std::endl;
        }
        if(who =='1'){
            box1->chooseCurrentBox(p.getMyFighter().getBody());
            std::cout << p.getMyFighter().getBody() << std::endl;
        }else{
            box2->chooseCurrentBox(p.getMyFighter().getBody());
        }
    }
    if(cpyState == "st-mp"){
        if(!p.getMyFighter().getMove(1).getStarted()) {
            p.playMoves(1);
            std::cout << "PLAY STANDING MEDIUM PUNCH" << std::endl;
            if(who == '1'){
                box1->clear();
                delete box1;
                box1 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }else{
                box2->clear();
                delete box2;
                box2 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }
        }
        p.updateMove(1);
        if(p.getMyFighter().getMove(1).getFinished()) {
            p.setPlayerState("st");
            p.getMyFighter().getMove(1).setFinished(false);
            p.getMyFighter().getMove(1).setStarted(false);
        }
        if(who =='1'){
            box1->chooseCurrentBox(p.getMyFighter().getBody());
            std::cout << p.getMyFighter().getBody() << std::endl;
        }else{
            box2->chooseCurrentBox(p.getMyFighter().getBody());
        }
    }
    if(cpyState == "st-hp"){
        if(!p.getMyFighter().getMove(2).getStarted()) {
            p.playMoves(2);
            std::cout << "PLAY STANDING HEAVY PUNCH" << std::endl;
            if(who == '1'){
                box1->clear();
                delete box1;
                box1 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }else{
                box2->clear();
                delete box2;
                box2 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }
        }
        p.updateMove(2);
        if(p.getMyFighter().getMove(2).getFinished()) {
            p.setPlayerState("st");
            p.getMyFighter().getMove(2).setFinished(false);
            p.getMyFighter().getMove(2).setStarted(false);
        }
        if(who =='1'){
            box1->chooseCurrentBox(p.getMyFighter().getBody());
            std::cout << p.getMyFighter().getBody() << std::endl;
        }else{
            box2->chooseCurrentBox(p.getMyFighter().getBody());
        }
    }
    if(cpyState == "st-lk"){
        if(!p.getMyFighter().getMove(3).getStarted()) {
            p.playMoves(3);
            std::cout << "PLAY STANDING LIGHT KICK" << std::endl;
            if(who == '1'){
                box1->clear();
                delete box1;
                box1 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }else{
                box2->clear();
                delete box2;
                box2 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }
        }
        p.updateMove(3);
        if(p.getMyFighter().getMove(3).getFinished()) {
            p.setPlayerState("st");
            p.getMyFighter().getMove(3).setFinished(false);
            p.getMyFighter().getMove(3).setStarted(false);
        }
        if(who =='1'){
            box1->chooseCurrentBox(p.getMyFighter().getBody());
            std::cout << p.getMyFighter().getBody() << std::endl;
        }else{
            box2->chooseCurrentBox(p.getMyFighter().getBody());
        }
    }
    if(cpyState == "st-mk"){
        if(!p.getMyFighter().getMove(4).getStarted()) {
            p.playMoves(4);
            std::cout << "PLAY STANDING MEDIUM KICK" << std::endl;
            if(who == '1'){
                box1->clear();
                delete box1;
                box1 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }else{
                box2->clear();
                delete box2;
                box2 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }
        }
        p.updateMove(4);
        if(p.getMyFighter().getMove(4).getFinished()) {
            p.setPlayerState("st");
            p.getMyFighter().getMove(4).setFinished(false);
            p.getMyFighter().getMove(4).setStarted(false);
        }
        if(who =='1'){
            box1->chooseCurrentBox(p.getMyFighter().getBody());
            std::cout << p.getMyFighter().getBody() << std::endl;
        }else{
            box2->chooseCurrentBox(p.getMyFighter().getBody());
        }
    }
    if(cpyState == "st-hk"){
        if(!p.getMyFighter().getMove(5).getStarted()) {
            p.playMoves(5);
            std::cout << "PLAY STANDING HEAVY KICK" << std::endl;
            if(who == '1'){
                box1->clear();
                delete box1;
                box1 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }else{
                box2->clear();
                delete box2;
                box2 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }
        }
        p.updateMove(5);
        if(p.getMyFighter().getMove(5).getFinished()) {
            p.setPlayerState("st");
            p.getMyFighter().getMove(5).setFinished(false);
            p.getMyFighter().getMove(5).setStarted(false);
        }
        if(who =='1'){
            box1->chooseCurrentBox(p.getMyFighter().getBody());
            std::cout << p.getMyFighter().getBody() << std::endl;
        }else{
            box2->chooseCurrentBox(p.getMyFighter().getBody());
        }
    }
    if(cpyState == "cr-lp"){
        if(!p.getMyFighter().getMove(6).getStarted()) {
            p.playMoves(6);
            std::cout << "PLAY CROUCHING LIGHT PUNCH" << std::endl;
            if(who == '1'){
                box1->clear();
                delete box1;
                box1 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }else{
                box2->clear();
                delete box2;
                box2 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }
        }
        p.updateMove(6);
        if(p.getMyFighter().getMove(6).getFinished()) {
            p.setPlayerState("st");
            p.getMyFighter().getMove(6).setFinished(false);
            p.getMyFighter().getMove(6).setStarted(false);
        }
        if(who =='1'){
            box1->chooseCurrentBox(p.getMyFighter().getBody());
            std::cout << p.getMyFighter().getBody() << std::endl;
        }else{
            box2->chooseCurrentBox(p.getMyFighter().getBody());
        }
    }
    if(cpyState == "cr-mp"){
        if(!p.getMyFighter().getMove(7).getStarted()) {
            p.playMoves(7);
            std::cout << "PLAY CROUCHING MEDIUM PUNCH" << std::endl;
            if(who == '1'){
                box1->clear();
                delete box1;
                box1 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }else{
                box2->clear();
                delete box2;
                box2 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }
        }
        p.updateMove(7);
        if(p.getMyFighter().getMove(7).getFinished()) {
            p.setPlayerState("st");
            p.getMyFighter().getMove(7).setFinished(false);
            p.getMyFighter().getMove(7).setStarted(false);
        }
        if(who =='1'){
            box1->chooseCurrentBox(p.getMyFighter().getBody());
            std::cout << p.getMyFighter().getBody() << std::endl;
        }else{
            box2->chooseCurrentBox(p.getMyFighter().getBody());
        }
    }
    if(cpyState == "cr-hp"){
        if(!p.getMyFighter().getMove(8).getStarted()) {
            p.playMoves(8);
            std::cout << "PLAY CROUCHING HEAVY PUNCH" << std::endl;
            if(who == '1'){
                box1->clear();
                delete box1;
                box1 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }else{
                box2->clear();
                delete box2;
                box2 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }
        }
        p.updateMove(8);
        if(p.getMyFighter().getMove(8).getFinished()) {
            p.setPlayerState("st");
            p.getMyFighter().getMove(8).setFinished(false);
            p.getMyFighter().getMove(8).setStarted(false);
        }
        if(who =='1'){
            box1->chooseCurrentBox(p.getMyFighter().getBody());
            std::cout << p.getMyFighter().getBody() << std::endl;
        }else{
            box2->chooseCurrentBox(p.getMyFighter().getBody());
        }
    }
    if(cpyState == "cr-lk"){
        if(!p.getMyFighter().getMove(9).getStarted()) {
            p.playMoves(9);
            std::cout << "PLAY CROUCHING LIGHT KICK" << std::endl;
            if(who == '1'){
                box1->clear();
                delete box1;
                box1 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }else{
                box2->clear();
                delete box2;
                box2 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }
        }
        p.updateMove(9);
        if(p.getMyFighter().getMove(9).getFinished()) {
            p.setPlayerState("st");
            p.getMyFighter().getMove(9).setFinished(false);
            p.getMyFighter().getMove(9).setStarted(false);
        }
        if(who =='1'){
            box1->chooseCurrentBox(p.getMyFighter().getBody());
            std::cout << p.getMyFighter().getBody() << std::endl;
        }else{
            box2->chooseCurrentBox(p.getMyFighter().getBody());
        }
    }
    if(cpyState == "cr-mk"){
        if(!p.getMyFighter().getMove(10).getStarted()) {
            p.playMoves(10);
            std::cout << "PLAY CROUCHING MEDIUM KICK" << std::endl;
            if(who == '1'){
                box1->clear();
                delete box1;
                box1 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }else{
                box2->clear();
                delete box2;
                box2 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }
        }
        p.updateMove(10);
        if(p.getMyFighter().getMove(10).getFinished()) {
            p.setPlayerState("cr");
            p.getMyFighter().getMove(10).setFinished(false);
            p.getMyFighter().getMove(10).setStarted(false);
        }
        if(who =='1'){
            box1->chooseCurrentBox(p.getMyFighter().getBody());
        }else{
            box2->chooseCurrentBox(p.getMyFighter().getBody());
        }
    }
    if(cpyState == "cr-hk"){
        if(!p.getMyFighter().getMove(11).getStarted()) {
            p.playMoves(11);
            std::cout << "PLAY CROUCHING HEAVY KICK" << std::endl;
            if(who == '1'){
                box1->clear();
                delete box1;
                box1 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }else{
                box2->clear();
                delete box2;
                box2 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }
        }
        p.updateMove(11);
        if(p.getMyFighter().getMove(11).getFinished()) {
            p.setPlayerState("st");
            p.getMyFighter().getMove(11).setFinished(false);
            p.getMyFighter().getMove(11).setStarted(false);
        }
        if(who =='1'){
            box1->chooseCurrentBox(p.getMyFighter().getBody());
        }else{
            box2->chooseCurrentBox(p.getMyFighter().getBody());
        }
    }
    if(cpyState == "special1"){
        if(!p.getMyFighter().getMove(12).getStarted()) {
            p.playMoves(12);
            std::cout << "HADOOOOOOOOOOOKEN !!!!" << std::endl;
        }
        p.updateMove(12);
        if(p.getMyFighter().getMove(12).getFinished()) {
            p.setPlayerState("st");
            p.getMyFighter().getMove(12).setFinished(false);
            p.getMyFighter().getMove(12).setStarted(false);
        }
        if(who =='1'){
            box1->chooseCurrentBox(p.getMyFighter().getBody());
            std::cout << p.getMyFighter().getBody() << std::endl;
        }else{
            box2->chooseCurrentBox(p.getMyFighter().getBody());
        }
    }
    if(cpyState == "special2"){
        if(!p.getMyFighter().getMove(13).getStarted()) {
            p.playMoves(13);
            std::cout << "TATSUMAKI SENPUKYAKU !!!" << std::endl;
        }
        p.updateMove(13);
        if(p.getMyFighter().getMove(13).getFinished()) {
            p.setPlayerState("st");
            p.getMyFighter().getMove(13).setFinished(false);
            p.getMyFighter().getMove(13).setStarted(false);
        }
    }
    if(cpyState == "cr"){
        if (!p.getMyFighter().getMovement(3).getStarted()) {
            p.playMovement(3);
            std::cout << "CROUCHING" << std::endl;
            if(who == '1'){
                box1->clear();
                delete box1;
                box1 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }else{
                box2->clear();
                delete box2;
                box2 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }
        }
        p.updateMovement(3);
        if (p.getMyFighter().getMovement(3).getFinished()) {
            //p.setPlayerState("st");
            p.getMyFighter().getMovement(3).setFinished(false);
            p.getMyFighter().getMovement(3).setStarted(false);
        }
        if(who =='1'){
            box1->chooseCurrentBox(p.getMyFighter().getBody());
        }else{
            box2->chooseCurrentBox(p.getMyFighter().getBody());
        }
    }
    if(cpyState == "cr-bw"){
        if (!p.getMyFighter().getMovement(6).getStarted()) {
            p.playMovement(6);
            std::cout << "CROUCHING BACKWARD" << std::endl;
            if(who == '1'){
                box1->clear();
                delete box1;
                box1 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }else{
                box2->clear();
                delete box2;
                box2 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }
        }
        p.updateMovement(6);
        if (p.getMyFighter().getMovement(6).getFinished()) {
            //p.setPlayerState("st");
            p.getMyFighter().getMovement(6).setFinished(false);
            p.getMyFighter().getMovement(6).setStarted(false);
        }
        if(who =='1'){
            box1->chooseCurrentBox(p.getMyFighter().getBody());
        }else{
            box2->chooseCurrentBox(p.getMyFighter().getBody());
        }
    }
    if(cpyState == "st") {
        if (!p.getMyFighter().getMovement(0).getStarted()) {
            p.playMovement(0);
            std::cout << "STANDING" << std::endl;
            if(who == '1'){
                box1->clear();
                delete box1;
                box1 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }else{
                box2->clear();
                delete box2;
                box2 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }
        }
        p.updateMovement(0);
        
        
        if (p.getMyFighter().getMovement(0).getFinished()) {
            //p.setPlayerState("st");
            p.getMyFighter().getMovement(0).setFinished(false);
            p.getMyFighter().getMovement(0).setStarted(false);
        }
        if(who =='1'){
            box1->chooseCurrentBox(p.getMyFighter().getBody());
        }else{
            box2->chooseCurrentBox(p.getMyFighter().getBody());
        }
    }
    if(cpyState == "st-fw"){
        if (!p.getMyFighter().getMovement(1).getStarted()) {
            p.playMovement(1);
            std::cout << "WALKING FORWARD" << std::endl;
            if(who == '1'){
                box1->clear();
                delete box1;
                box1 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }else{
                box2->clear();
                delete box2;
                box2 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }
        }
        p.updateMovement(1);
        
        if (p.getMyFighter().getMovement(1).getFinished()) {
            //p.setPlayerState("st");
            p.getMyFighter().getMovement(1).setFinished(false);
            p.getMyFighter().getMovement(1).setStarted(false);
        }
        if(p.getPositionX() < otherPlayerPosX) {
            p.getPosition().moveRight();
        }else{
            p.getPosition().moveLeft();
        }
        if(who =='1'){
            box1->chooseCurrentBox(p.getMyFighter().getBody());
        }else{
            box2->chooseCurrentBox(p.getMyFighter().getBody());
        }
    }
    if(cpyState == "st-bw"){
        if (!p.getMyFighter().getMovement(2).getStarted()) {
            p.playMovement(2);
            std::cout << "WALKING BACKWARD" << std::endl;
            if(who == '1'){
                box1->clear();
                delete box1;
                box1 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }else{
                box2->clear();
                delete box2;
                box2 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }
        }
         p.updateMovement(2);
        
        if (p.getMyFighter().getMovement(2).getFinished()) {
            //p.setPlayerState("st");
            p.getMyFighter().getMovement(2).setFinished(false);
            p.getMyFighter().getMovement(2).setStarted(false);
        }
        if(p.getPositionX() < otherPlayerPosX) {
            p.getPosition().moveLeft();
        }else{
            p.getPosition().moveRight();
        }
        if(who =='1'){
            box1->chooseCurrentBox(p.getMyFighter().getBody());
        }else{
            box2->chooseCurrentBox(p.getMyFighter().getBody());
        }
    }
    if(cpyState == "cr-bk"){
        if (!p.getMyFighter().getMovement(4).getStarted()) {
            p.playMovement(4);
            std::cout << "CROUCHED BACKWARD" << std::endl;
            if(who == '1'){
                box1->clear();
                delete box1;
                box1 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }else{
                box2->clear();
                delete box2;
                box2 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }
        }
         p.updateMovement(4);

        if (p.getMyFighter().getMovement(4).getFinished()) {
            //p.setPlayerState("st");
            p.getMyFighter().getMovement(4).setFinished(false);
            p.getMyFighter().getMovement(4).setStarted(false);
        }

        if(who =='1'){
            box1->chooseCurrentBox(p.getMyFighter().getBody());
        }else{
            box2->chooseCurrentBox(p.getMyFighter().getBody());
        }
    }
    if(cpyState == "st-bk"){
        if (!p.getMyFighter().getMovement(5).getStarted()) {
            p.playMovement(5);
            std::cout << "WALKING BACKWARD" << std::endl;
            if(who == '1'){
                box1->clear();
                delete box1;
                box1 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }else{
                box2->clear();
                delete box2;
                box2 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }
        }
         p.updateMovement(5);

        if (p.getMyFighter().getMovement(5).getFinished()) {
            //p.setPlayerState("st");
            p.getMyFighter().getMovement(5).setFinished(false);
            p.getMyFighter().getMovement(5).setStarted(false);
        }

        if(who =='1'){
            box1->chooseCurrentBox(p.getMyFighter().getBody());
        }else{
            box2->chooseCurrentBox(p.getMyFighter().getBody());
        }
    }
    if(cpyState == "st-hit"){
        if (!p.getMyFighter().getMovement(7).getStarted()) {
            p.playMovement(7);
            if(who == '1'){
                box1->clear();
                delete box1;
                box1 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }else{
                box2->clear();
                delete box2;
                box2 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }
        }
        p.updateMovement(7);

        if (p.getMyFighter().getMovement(7).getFinished()) {
            //p.setPlayerState("st");
            p.getMyFighter().getMovement(7).setFinished(false);
            p.getMyFighter().getMovement(7).setStarted(false);
        }

        if(who =='1'){
            box1->chooseCurrentBox(p.getMyFighter().getBody());
        }else{
            box2->chooseCurrentBox(p.getMyFighter().getBody());
        }
    }
    if(cpyState == "cr-hit"){
        if (!p.getMyFighter().getMovement(8).getStarted()) {
            p.playMovement(8);
            if(who == '1'){
                box1->clear();
                delete box1;
                box1 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }else{
                box2->clear();
                delete box2;
                box2 = new Boxcolliders(renderer,p,p.getMyFighter().getFighterName(),p.getPlayerState(),side);
            }
        }
        p.updateMovement(8);

        if (p.getMyFighter().getMovement(8).getFinished()) {
            //p.setPlayerState("st");
            p.getMyFighter().getMovement(8).setFinished(false);
            p.getMyFighter().getMovement(8).setStarted(false);
        }

        if(who =='1'){
            box1->chooseCurrentBox(p.getMyFighter().getBody());
        }else{
            box2->chooseCurrentBox(p.getMyFighter().getBody());
        }
    }
    if(cpyState == "fj"){
        std::cout << "FORWARD JUMP" << std::endl;
        if (!p.getMyFighter().getMovement(11).getStarted()) {
            p.playMovement(11);
        }
        p.updateMovement(11);
        p.setPositionY(p.getPositionY()-2);
        if(side == 'L'){
            p.setPositionX(p.getPositionX()+1);
        }else{
            p.setPositionX(p.getPositionX()-1);
        }
        if (p.getMyFighter().getMovement(11).getFinished()) {
            p.setPositionY(p.getPositionY()-2);
            if(side == 'L'){
                p.setPositionX(p.getPositionX()+1);
            }else{
                p.setPositionX(p.getPositionX()-1);
            }
            p.setPlayerState("fj-down");
            p.getMyFighter().getMovement(11).setFinished(false);
            p.getMyFighter().getMovement(11).setStarted(false);
        }
    }
    if(cpyState == "fj-down"){
        std::cout << "FORWARD JUMP" << std::endl;
        if (!p.getMyFighter().getMovement(12).getStarted()) {
            p.playMovement(12);
        }
        p.updateMovement(12);
        p.setPositionY(p.getPositionY()+4);
        if(side == 'L'){
            p.setPositionX(p.getPositionX()+1);
        }else{
            p.setPositionX(p.getPositionX()-1);
        }
        if (p.getMyFighter().getMovement(12).getFinished()) {
            p.setPlayerState("st");
            p.getMyFighter().getMovement(12).setFinished(false);
            p.getMyFighter().getMovement(12).setStarted(false);
        }
    }
    if(cpyState == "bj"){
        std::cout << "BACKWARD JUMP" << std::endl;
        if (!p.getMyFighter().getMovement(13).getStarted()) {
            p.playMovement(13);
        }
        p.updateMovement(13);
        p.setPositionY(p.getPositionY()-2);
        if(side == 'L'){
            p.setPositionX(p.getPositionX()-1);
        }else{
            p.setPositionX(p.getPositionX()+1);
        }
        if (p.getMyFighter().getMovement(13).getFinished()) {
            p.setPositionY(p.getPositionY()-2);
            if(side == 'L'){
                p.setPositionX(p.getPositionX()-1);
            }else{
                p.setPositionX(p.getPositionX()+1);
            }
            p.setPlayerState("bj-down");
            p.getMyFighter().getMovement(13).setFinished(false);
            p.getMyFighter().getMovement(13).setStarted(false);
        }
    }
    if(cpyState == "bj-down"){
        std::cout << "BACKWARD JUMP" << std::endl;
        if (!p.getMyFighter().getMovement(14).getStarted()) {
            p.playMovement(14);
        }
        p.updateMovement(14);
        p.setPositionY(p.getPositionY()+4);
        if(side == 'L'){
            p.setPositionX(p.getPositionX()-1);
        }else{
            p.setPositionX(p.getPositionX()+1);
        }
        if (p.getMyFighter().getMovement(14).getFinished()) {
            p.setPlayerState("st");
            p.getMyFighter().getMovement(14).setFinished(false);
            p.getMyFighter().getMovement(14).setStarted(false);
        }
    }
    if(cpyState == "nj"){
        std::cout << "NEUTRAL JUMP" << std::endl;
        if (!p.getMyFighter().getMovement(9).getStarted()) {
            p.playMovement(9);
        }
        p.updateMovement(9);
        p.setPositionY(p.getPositionY()-2);
        if (p.getMyFighter().getMovement(9).getFinished()) {
            p.setPositionY(p.getPositionY()-2);
            p.setPlayerState("nj-down");
            p.getMyFighter().getMovement(9).setFinished(false);
            p.getMyFighter().getMovement(9).setStarted(false);
        }
    }
    if(cpyState == "nj-down"){
        std::cout << "NEUTRAL JUMP" << std::endl;
        if (!p.getMyFighter().getMovement(10).getStarted()) {
            p.playMovement(10);
        }
        p.updateMovement(10);
        p.setPositionY(p.getPositionY()+4);
        if (p.getMyFighter().getMovement(10).getFinished()) {
            p.setPlayerState("st");
            p.getMyFighter().getMovement(10).setFinished(false);
            p.getMyFighter().getMovement(10).setStarted(false);
        }
    }

    if(p.getPositionX() < 0 + p1Sprite->getSpriteWidth()/2)
        p.getPosition().moveRight();
    if(p.getPositionX() > 384 - p1Sprite->getSpriteWidth()/2)
        p.getPosition().moveLeft();
    if(who == '1'){
        box1->update(p);
    }else{
        box2->update(p);
    }
    p.blockStunState(otherPlayer);
    p.hitStunState(otherPlayer);
    //UI->update();
}

void Ihm::run() {
    while(isRun){
        if(t.isOK()) {
            update();

            //buffer.testPrintbuffer();
            if(true) {
                map->updateMap(*p1, *p2);
                buffer.addBuffer();
                buffer.saveToList(p1->setInputs(), '0');
                buffer.saveToList(p2->setInputs(), '1');

                p1->checkInput(p2->getPositionX());
                p2Sprite->updateSprite(*p2, p1->getPositionX());

                if (p1->getPositionX() < p2->getPositionX()) {
                    updateEntity(*p1, p2->getPositionX(), '1', 'L', *p2);
                } else {
                    updateEntity(*p1, p2->getPositionX(), '1', 'R', *p2);
                }
                p1Sprite->updateSprite(*p1, p2->getPositionX());
                p2->checkInput(p1->getPositionX());

                if (p2->getPositionX() < p1->getPositionX()) {
                    updateEntity(*p2, p1->getPositionX(), '2', 'L', *p1);
                } else {
                    updateEntity(*p2, p1->getPositionX(), '2', 'R', *p1);
                }
                if (p1->getPlayerState() == "st-bw") {
                    if ((p2->getPlayerState() != "st") && (p2->getPlayerState() != "st-fw") &&
                        (p2->getPlayerState() != "st-bw") && (p2->getPlayerState() != "cr") &&
                        (p2->getPlayerState() != "cr-bw") && (p2->getPlayerState() != "cr-bk") &&
                        (p2->getPlayerState() != "st-bk") && (p2->getPlayerState() != "cr-hit") &&
                        (p2->getPlayerState() != "st-hit")) {
                        p1->setPlayerState("st-bk");
                    }

                }
                if (p1->getPlayerState() == "st-bk") {
                    if (((p2->getPlayerState() == "st") || (p2->getPlayerState() == "st-fw") ||
                         (p2->getPlayerState() == "st-bw") || (p2->getPlayerState() == "cr") ||
                         (p2->getPlayerState() == "cr-bw") || (p2->getPlayerState() == "st-bk") ||
                         (p2->getPlayerState() == "cr-bk") || (p2->getPlayerState() == "nj") ||
                         (p2->getPlayerState() == "nj-down") || (p2->getPlayerState() == "fj") ||
                         (p2->getPlayerState() == "fj-down") || (p2->getPlayerState() == "bj") ||
                         (p2->getPlayerState() == "bj-down")) && (p1->getBlockStun() == 0)) {
                        p1->setPlayerState("st-bw");
                    }
                }

                if (p1->getPlayerState() == "cr-bw") {
                    if ((p2->getPlayerState() != "st") && (p2->getPlayerState() != "st-fw") &&
                        (p2->getPlayerState() != "st-bw") && (p2->getPlayerState() != "cr") &&
                        (p2->getPlayerState() != "cr-bw") && (p2->getPlayerState() != "cr-bk") &&
                        (p2->getPlayerState() != "st-bk") && (p2->getPlayerState() != "cr-hit") &&
                        (p2->getPlayerState() != "st-hit")) {
                        p1->setPlayerState("cr-bk");
                    } else {
                        p1->setPlayerState("cr");
                    }
                }

                if (p1->getPlayerState() == "cr-bk") {
                    if (((p2->getPlayerState() == "st") || (p2->getPlayerState() == "st-fw") ||
                         (p2->getPlayerState() == "st-bw") || (p2->getPlayerState() == "cr") ||
                         (p2->getPlayerState() == "cr-bw") || (p2->getPlayerState() == "st-bk") ||
                         (p2->getPlayerState() == "cr-bk") || (p2->getPlayerState() == "nj") ||
                         (p2->getPlayerState() == "nj-down") || (p2->getPlayerState() == "fj") ||
                         (p2->getPlayerState() == "fj-down") || (p2->getPlayerState() == "bj") ||
                         (p2->getPlayerState() == "bj-down")) && (p1->getBlockStun() == 0)) {
                        p1->setPlayerState("cr");
                    }
                }
                if (p2->getPlayerState() == "st-bw") {
                    if ((p1->getPlayerState() != "st") && (p1->getPlayerState() != "st-fw") &&
                        (p1->getPlayerState() != "st-bw") && (p1->getPlayerState() != "cr") &&
                        (p1->getPlayerState() != "cr-bw") && (p1->getPlayerState() != "cr-bk") &&
                        (p1->getPlayerState() != "st-bk") && (p1->getPlayerState() != "cr-hit") &&
                        (p1->getPlayerState() != "st-hit") && (p2->getPlayerState() != "nj") &&
                        (p2->getPlayerState() != "nj-down") && (p2->getPlayerState() != "fj") &&
                        (p2->getPlayerState() != "fj-down") && (p2->getPlayerState() != "bj") &&
                        (p2->getPlayerState() != "bj-down")) {
                        p2->setPlayerState("st-bk");
                    }
                }
                if (p2->getPlayerState() == "st-bk") {
                    if (((p1->getPlayerState() == "st") || (p1->getPlayerState() == "st-fw") ||
                         (p1->getPlayerState() == "st-bw") || (p1->getPlayerState() == "cr") ||
                         (p1->getPlayerState() == "cr-bw") || (p1->getPlayerState() == "st-bk") ||
                         (p1->getPlayerState() == "cr-bk") || (p1->getPlayerState() == "nj") ||
                         (p1->getPlayerState() == "nj-down") || (p1->getPlayerState() == "fj") ||
                         (p1->getPlayerState() == "fj-down") || (p1->getPlayerState() == "bj") ||
                         (p1->getPlayerState() == "bj-down")) && (p2->getBlockStun() == 0)) {
                        p2->setPlayerState("st-bw");
                    }
                }

                if (p2->getPlayerState() == "cr-bw") {
                    if ((p1->getPlayerState() != "st") && (p1->getPlayerState() != "st-fw") &&
                        (p1->getPlayerState() != "st-bw") && (p1->getPlayerState() != "cr") &&
                        (p1->getPlayerState() != "cr-bw") && (p1->getPlayerState() != "cr-bk") &&
                        (p1->getPlayerState() != "st-bk") && (p1->getPlayerState() != "cr-hit") &&
                        (p1->getPlayerState() != "st-hit") && (p1->getPlayerState() != "nj") &&
                        (p1->getPlayerState() != "nj-down") && (p1->getPlayerState() != "fj") &&
                        (p1->getPlayerState() != "fj-down") && (p1->getPlayerState() != "bj") &&
                        (p1->getPlayerState() != "bj-down")) {
                        p2->setPlayerState("cr-bk");
                    } else {
                        p2->setPlayerState("cr");

                    }
                }

                if (p2->getPlayerState() == "cr-bk") {
                    if (((p1->getPlayerState() == "st") || (p1->getPlayerState() == "st-fw") ||
                         (p1->getPlayerState() == "st-bw") || (p1->getPlayerState() == "cr") ||
                         (p1->getPlayerState() == "cr-bw") || (p1->getPlayerState() == "st-bk") ||
                         (p1->getPlayerState() == "cr-bk") || (p1->getPlayerState() == "nj") ||
                         (p1->getPlayerState() == "nj-down") || (p1->getPlayerState() == "fj") ||
                         (p1->getPlayerState() == "fj-down") || (p1->getPlayerState() == "bj") ||
                         (p1->getPlayerState() == "bj-down")) && (p2->getBlockStun() == 0)) {
                        p2->setPlayerState("cr");
                    }
                }

                //updateEntity(*p2,p1->getPositionX(),'2');

                //p1->testPrintInputs();
                //p2->testPrintInputs();
            }
            draw();
            //buffer.testPrintBufferGlobal();
        }
    }
}

