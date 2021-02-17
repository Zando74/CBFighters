//
// Created by nino on 28/03/2020.
//

#include "Movement.h"
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <time.h>

Movement::Movement(std::string & fighterName, std::string & movementName)
{
    cpt = 0;
    cptMovement = 0;
    Started = false;
    Finished = false;
    std::ifstream movementFile("data/characters/" + fighterName + "/" + movementName + "/" + movementName + ".txt"); //variable
    int current = 0;
    movementAction ac;
    if(movementFile.is_open()){
        movementFile >> nbFrames;
        while(current < nbFrames){
                movementFile >> ac.img >> ac.frames;
                list.push_back(ac);
                current++;
        }
    }else{
        std::cout << "erreur durant l'ouverture du fichier data/characters/" << fighterName << "/" << movementName << "/" << movementName << ".txt" << std::endl;
        exit(EXIT_FAILURE);
    }
    movementFile.close();
}

Movement::~Movement()
{
    list.clear();
    cpList.clear();
}

void Movement::start(const char &bodyFighter)
{
    Started = true;
    currentList = 1;
    cptMovement = 0;
    cpt = 0;
    previousBody = bodyFighter;
    cpList.assign(list.begin(), list.end());
}

void Movement::update(char &bodyFighter) {
    if(currentList == 0){
        return;
    }else if(currentList == 1){
        play(bodyFighter);
    }
}

void Movement::play(char &bodyFighter) {
    if(cptMovement < nbFrames) {
        movementAction ac = cpList.front();
        if (cpt < ac.frames) {
            bodyFighter = ac.img;
            cpt++;
            return;
        } else {
            cpList.pop_front();
            cpt = 0;
            cptMovement++;
            play(bodyFighter);
        }
    }else{
        cpt = 0;
        cptMovement = 0;
        currentList = 0;
        bodyFighter = previousBody;
        Finished = true;
    }
}


bool Movement::getStarted() const {
    return Started;
}

bool Movement::getFinished() const {
    return Finished;
}

void Movement::setStarted(bool b) {
    Started = b;
}

void Movement::setFinished(bool b) {
    Finished = b;
}

void Movement::testRegression()
{
    srand(time(NULL));
    char bodyFighter = 'a';
    int alea;
    for(int i=0;i<100000;i++){
        alea = rand()%10;
        if(alea == 1){
            start(bodyFighter);
            std::cout << " mouvement reinitialisé ! " << std::endl;
        }
        update(bodyFighter);
        std::cout <<" etat du mouvement : " << '[' << bodyFighter << ']' << std::endl;
    }
}