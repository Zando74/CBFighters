#include <list>
#include <vector>
#include <fstream>
#include <iostream>
#include "Fighters.h"
#include "Moves.h"
#include "Movement.h"
#include <cassert>
#include <time.h>


Fighters::Fighters(std::string & name) {
    fighterName = name;
    std::ifstream characterFile("data/characters/" + name + "/" + name + ".txt");
    if(characterFile.is_open())
        characterFile >> body;
    else{
        std::cout << "The character " << name << " doesn't exists";
        exit(EXIT_FAILURE);
    }
    characterFile.close();
    std::string moveName = "st-lp";
    Moves stlp(name,moveName);
    movelist.push_back(stlp);

    moveName = "st-mp";
    Moves stmp(name,moveName);
    movelist.push_back(stmp);

    moveName = "st-hp";
    Moves sthp(name,moveName);
    movelist.push_back(sthp);

    moveName = "st-lk";
    Moves stlk(name,moveName);
    movelist.push_back(stlk);

    moveName = "st-mk";
    Moves stmk(name,moveName);
    movelist.push_back(stmk);

    moveName = "st-hk";
    Moves sthk(name,moveName);
    movelist.push_back(sthk);

    moveName = "cr-lp";
    Moves crlp(name,moveName);
    movelist.push_back(crlp);

    moveName = "cr-mp";
    Moves crmp(name,moveName);
    movelist.push_back(crmp);

    moveName = "cr-hp";
    Moves crhp(name,moveName);
    movelist.push_back(crhp);

    moveName = "cr-lk";
    Moves crlk(name,moveName);
    movelist.push_back(crlk);

    moveName = "cr-mk";
    Moves crmk(name,moveName);
    movelist.push_back(crmk);

    moveName = "cr-hk";
    Moves crhk(name,moveName);
    movelist.push_back(crhk);

    moveName = "special1";
    Moves special1(name,moveName);
    movelist.push_back(special1);

    moveName = "special2";
    Moves special2(name,moveName);
    movelist.push_back(special2);

    std::string movementName = "st";
    Movement st(name,movementName);
    movementList.push_back(st);

    movementName = "st-fw";
    Movement stfw(name,movementName);
    movementList.push_back(stfw);

    movementName = "st-bw";
    Movement stbw(name,movementName);
    movementList.push_back(stbw);

    movementName = "cr";
    Movement cr(name,movementName);
    movementList.push_back(cr);

    movementName = "cr-bk";
    Movement crbk(name, movementName);
    movementList.push_back(crbk);

    movementName = "st-bk";
    Movement stbk(name, movementName);
    movementList.push_back(stbk);

    movementName = "cr-bw";
    Movement crbw(name, movementName);
    movementList.push_back(crbw);

    movementName = "st-hit";
    Movement sthit(name, movementName);
    movementList.push_back(sthit);

    movementName = "cr-hit";
    Movement crhit(name, movementName);
    movementList.push_back(crhit);

    movementName = "nj";
    Movement nj(name,movementName);
    movementList.push_back(nj);
    movementName = "nj-down";
    Movement njdw(name,movementName);
    movementList.push_back(njdw);

    movementName = "fj";
    Movement fj(name,movementName);
    movementList.push_back(fj);
    movementName = "fj-down";
    Movement fjdw(name,movementName);
    movementList.push_back(fjdw);

    movementName = "bj";
    Movement bj(name,movementName);
    movementList.push_back(bj);
    movementName = "bj-down";
    Movement bjdw(name,movementName);
    movementList.push_back(bjdw);
}

Fighters::~Fighters() {}

char& Fighters::getBody() {
    return body;
}

void Fighters::setBody(char &c) {
    body = c;
}

Moves& Fighters::getMove(const int & i){
    assert((unsigned int)i < movelist.size());
    return movelist.at(i);
}

Movement& Fighters::getMovement(const int &i) {
    assert((unsigned int)i < movementList.size());
    return movementList.at(i);
}

std::string Fighters::getFighterName() {
    return fighterName;
}

void Fighters::testRegression(){
    srand(time(NULL));
    for(int i=0;i<100000;i++){
        int randomMovesIndice = rand() % movelist.size();
        Moves randomMoves = getMove(randomMovesIndice);
        std::cout << "Coups numéro : " << randomMovesIndice << std::endl;
        int randomMovementIndice = rand() % movementList.size();
        Movement randomMovement = getMovement(randomMovementIndice);
        std::cout << "déplacement numéro : " << randomMovementIndice << std::endl;  
    }
}