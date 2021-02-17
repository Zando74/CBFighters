//
// Created by jessim and ferrer on 26/02/2020.
//
//test
#include "Moves.h"
#include <iostream>
#include <fstream>
#include <list>
#include <string>

Moves::Moves(std::string & fighterName, std::string & moveName)
{
    cpt = 0;
    cptMove = 0;
    Started = false;
    Finished = false;
    std::ifstream moveFile("data/characters/" + fighterName + "/" + moveName + "/" + moveName + ".txt"); //variable
    int current = 0;
    action ac;
    if(moveFile.is_open()){
        moveFile >> nbStartup >> nbActive >> nbRecovery;
        while(current < nbRecovery+nbActive+nbStartup){
            if(current < nbStartup){
                moveFile >> ac.img >> ac.frames;
                listStartup.push_back(ac);
                current++;
            }else if(current < nbStartup+nbActive){
                moveFile >> ac.img >> ac.frames;
                listActive.push_back(ac);
                current++;
            }else{
                moveFile >> ac.img >> ac.frames;
                listRecovery.push_back(ac);
                current++;
            }
        }
    }else{
        std::cout << "erreur durant l'ouverture du fichier data/characters/" << fighterName << "/" << moveName << "/" << moveName << ".txt" << std::endl;
        exit(EXIT_FAILURE);
    }
    moveFile.close();
}

Moves::~Moves()
{
    listStartup.clear();
    cpListStartup.clear();
    listActive.clear();
    cpListActive.clear();
    listRecovery.clear();
    cpListRecovery.clear();
}

void Moves::start(const char &bodyFighter)
{
    Started = true;
    currentList = 1;
    cptMove = 0;
    cpt = 0;
    previousBody = bodyFighter;
    cpListStartup.assign(listStartup.begin(), listStartup.end());
    cpListActive.assign(listActive.begin(), listActive.end());
    cpListRecovery.assign(listRecovery.begin(), listRecovery.end());
}

void Moves::updateMove(char &bodyFighter) {
    if(currentList == 0){
        return;
    }else if(currentList == 1){
        playStartup(bodyFighter);
    }else if(currentList == 2){
        playActive(bodyFighter);
    }else if(currentList == 3){
        playRecovery(bodyFighter);
    }
}

void Moves::playStartup(char &bodyFighter) {
    if(cptMove < nbStartup) {
        action ac = cpListStartup.front();
        if (cpt < ac.frames) {
            bodyFighter = ac.img;
            cpt++;
            return;
        } else {
            cpListStartup.pop_front();
            cpt = 0;
            cptMove++;
            playStartup(bodyFighter);
        }
    }else{
        cpt = 0;
        cptMove = 0;
        currentList = 2;
        playActive(bodyFighter);
    }
}

void Moves::playActive(char &bodyFighter) {
    if(cptMove < nbActive) {
        action ac = cpListActive.front();
        if (cpt < ac.frames) {
            bodyFighter = ac.img;
            cpt++;
            return;
        } else {
            cpListActive.pop_front();
            cpt = 0;
            cptMove++;
            playActive(bodyFighter);
        }
    }else{
        cpt = 0;
        cptMove = 0;
        currentList = 3;
        playRecovery(bodyFighter);
    }
}

void Moves::playRecovery(char &bodyFighter) {
    if(cptMove < nbRecovery) {
        action ac = cpListRecovery.front();
        if (cpt < ac.frames) {
            bodyFighter = ac.img;
            cpt++;
            return;
        } else {
            cpListRecovery.pop_front();
            cpt = 0;
            cptMove++;
            playRecovery(bodyFighter);
        }
    }else{
        cpt = 0;
        currentList = 0;
        bodyFighter = previousBody;
        Finished = true;
    }
}

bool Moves::getStarted() const {
    return Started;
}

bool Moves::getFinished() const {
    return Finished;
}

void Moves::setStarted(bool b) {
    Started = b;
}

void Moves::setFinished(bool b) {
    Finished = b;
}

void Moves::testRegression()
{
    srand(time(NULL));
    char bodyFighter = 'a';
    int alea;
    for(int i=0;i<100000;i++){
        alea = rand()%10;
        if(alea == 1){
            start(bodyFighter);
            std::cout << " coup reinitialisé ! " << std::endl;
        }
        updateMove(bodyFighter);
        std::cout <<" etat du coup : " << '[' << bodyFighter << ']' << std::endl;
    }
}