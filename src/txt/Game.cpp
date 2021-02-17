#include "Game.h"
#include <iostream>
#include <string>
#include "../core/Player.h"
#include "../core/Timer.h"
#include "Map.h"
#include "Input.h"
#include "../core/CircularBuffer.h"

Game::Game(string& nameFighter1, string& nameFighter2) {
    isRun = true;
    p1 = new Player(nameFighter1,7,20);
    p2 = new Player(nameFighter2,7,26);
    world.initPlayerOnMap(*p1,*p2);
}
Game::~Game() {
    delete p1;
    delete p2;
}


void Game::moveEntity()
{
    std::string cpyState = p1->getPlayerState();
    if(cpyState == "st-fw"){
        if(world.isValidePosition(p1->getPositionX()+1,p1->getPositionY())){
            world.setElementHere(p1->getPositionX(),p1->getPositionY(),'.');
            p1->getPosition().moveLeft();
            world.setElementHere(p1->getPositionX(),p1->getPositionY(),p1->getBodyFighter());
        }
    }
    if(cpyState == "st-bw"){
        if(world.isValidePosition(p1->getPositionX()+1,p1->getPositionY())){
            world.setElementHere(p1->getPositionX(),p1->getPositionY(),'.');
            p1->getPosition().moveRight();
            world.setElementHere(p1->getPositionX(),p1->getPositionY(),p1->getBodyFighter());
        }
    }
    if(cpyState == "st-mp"){
        if(!p1->getMyFighter().getMove(0).getStarted())
            p1->playMoves(0);
        p1->updateMove(0);
        if(p1->getMyFighter().getMove(0).getFinished()) {
            p1->setPlayerState("st");
            p1->getMyFighter().getMove(0).setFinished(false);
            p1->getMyFighter().getMove(0).setStarted(false);
        }
    }
    cpyState = p2->getPlayerState();
    if(cpyState == "st-fw"){
        if(world.isValidePosition(p2->getPositionX()+1,p2->getPositionY())){
            world.setElementHere(p2->getPositionX(),p2->getPositionY(),'.');
            p2->getPosition().moveLeft();
            world.setElementHere(p2->getPositionX(),p2->getPositionY(),p2->getBodyFighter());
        }
    }

    if(cpyState == "st-bw"){
        if(world.isValidePosition(p2->getPositionX()+1,p2->getPositionY())){
            world.setElementHere(p2->getPositionX(),p2->getPositionY(),'.');
            p2->getPosition().moveRight();
            world.setElementHere(p2->getPositionX(),p2->getPositionY(),p2->getBodyFighter());
        }
    }

    if(cpyState == "st-mp"){
        if(!p2->getMyFighter().getMove(0).getStarted())
            p2->playMoves(0);
        p2->updateMove(0);
        if(p2->getMyFighter().getMove(0).getFinished()) {
            p2->setPlayerState("st");
            p2->getMyFighter().getMove(0).setFinished(false);
            p2->getMyFighter().getMove(0).setStarted(false);
        }
    }
}

void Game::update()
{
    hear.listenInput();
    buffer.addBuffer();
    buffer.addInput(hear.getInput());
    buffer.saveToList(p1->setInputs(),'0');
    buffer.saveToList(p2->setInputs(),'1');
    p1->checkInput(p2->getPositionX());
    p2->checkInput(p1->getPositionX());
    // Player update
    moveEntity();
    world.setPlayerOnMap(*p1,*p2);
}

void Game::draw()
{
    world.drawMap();
}

void Game::run() {
    while (isRun) {
        if (t.isOK()) {
            update();
            draw();
        }
    }
}