#include "Player.h"
#include "Fighters.h"
//#include "Timer.h"
#include <string>
#include <iostream>
#include <vector>
#include <time.h>

Player::Player(std::string &fighterName, int x, int y) {

    myFighter = new Fighters(fighterName);
    playerState = "st";
    blockStun = 0;
    hitStun = 0;
    myPosition.setPosX(x);
    myPosition.setPosY(y);
}

Player::~Player() {
    delete myFighter;
    myFighter = nullptr;
}

void Player::playMoves(int indice) {
    myFighter->getMove(indice).start(myFighter->getBody());
}

void Player::playMovement(int indice) {
    myFighter->getMovement(indice).start(myFighter->getBody());
}

void Player::updateMove(int indice) {
    myFighter->getMove(indice).updateMove(myFighter->getBody());
}

void Player::updateMovement(int indice) {
    myFighter->getMovement(indice).update(myFighter->getBody());
}

char& Player::getBodyFighter() const {
    return myFighter->getBody();
}

std::string Player::getPlayerState() {
    return playerState;
}

void Player::setPlayerState(std::string state) {
    playerState = state;
}

int Player::getPositionX() {
    return myPosition.getPosX();
}

int Player::getPositionY() {
    return myPosition.getPosY();
}

Position & Player::getPosition() {
    return myPosition;
}

void Player::setPositionX(const int pX) {
    myPosition.setPosX(pX);
}

void Player::setPositionY(const int pY) {
    myPosition.setPosY(pY);
}

std::vector<std::vector<char>>& Player::setInputs() {
    return inputs;
}

const std::vector<std::vector<char>>& Player::getInputs() {
    return inputs;
}

void Player::testPrintInputs() {
    std::cout << "list input of Player content : " << std::endl;
    for(unsigned int i=0;i<inputs.size();i++){
        std::cout << "[" << inputs[i][0] << "|" << inputs[i][1] << "|" << inputs[i][2] << "]" << " ";
    }
    std::cout << std::endl;
}
/*
void Player::checkInput(int xPosOfOtherPlayer) {
    if((inputs.back() == ' ') && ((playerState == "neutral") || (playerState == "forwardWalk") || (playerState == "backwardWalk"))){
        playerState = "neutral";
    }
    if(((inputs.back() == 'q') || (inputs.back() == 'k')) && ((playerState == "neutral") || (playerState == "forwardWalk") || (playerState == "backwardWalk"))){
        if(xPosOfOtherPlayer < getPositionX())
            playerState = "backwardWalk";
        playerState = "forwardWalk";
    }
    if((inputs.back() == 'd' || inputs.back() == 'm') && ((playerState == "neutral") || (playerState == "forwardWalk") || (playerState == "backwardWalk"))){
        if(xPosOfOtherPlayer < getPositionX())
            playerState = "forwardWalk";
        playerState = "backwardWalk";
    }
    if(((inputs.back() == 't') || (inputs.back() == 'p')) && ((playerState == "neutral")||(playerState == "forwardWalk")||(playerState == "backwardWalk")))
    {
        playerState = "st-mp";
    }
}
*/
void Player::checkInput(int otherPlayerPosX) {
    bool st = false;bool cr = false; bool nj = false; //standing / crouched / neutral jump / diagonal jump
    bool forward=false; bool backward = false;
    bool lp = false;bool mp = false; bool hp = false;bool lk = false; bool mk = false; bool hk = false; //low / medium / high / punch / kick

    // SPECIALMOVES
    bool right = false; bool left = false; bool down = false;
    bool downRight = false; bool downLeft = false;

    if((playerState == "st")||(playerState == "cr")||(playerState == "st-fw")||(playerState == "st-bw")) {
        for (int i = inputs.size() - 1; i >= 0; i--) {
            if (!lp && !mp && !hp && !lk && !mk && !hk) {
                for (int j = 0; j < 3; j++) {
                    char cp = inputs.back()[j];
                    if ((cp == 'u') || (cp == '7')) {
                        lp = true;
                    }
                    if ((cp == 'i') || (cp == '8')) {
                        mp = true;
                    }
                    if ((cp == 'o') || (cp == '9')) {
                        hp = true;
                    }
                    if ((cp == 'j') || (cp == '4')) {
                        lk = true;
                    }
                    if ((cp == 'k') || (cp == '5')) {
                        mk = true;
                    }
                    if ((cp == 'l') || (cp == '6')) {
                        hk = true;
                    }
                    if (((cp == 'd') || (cp == 'v')) /*&& (!cr)*/) {
                        if(getPositionX() < otherPlayerPosX) {
                            forward = true;
                        }else{
                            backward = true;
                        }
                        st = true;
                    }
                    if (((cp == 'q') || (cp == 'x')) && (!cr)) {
                        if(getPositionX() > otherPlayerPosX) {
                            forward = true;
                        }else{
                            backward = true;
                        }
                        st = true;
                    }
                    if ((cp == 's') || (cp == 'c')) {
                        cr = true;
                        st = false;
                    }
                    if((cp =='z')||(cp == 'w')){
                        nj = true;
                    }
                }
                if (st && lp) {
                    playerState = "st-lp";
                    return;
                }
                if (st && mp) {
                    playerState = "st-mp";
                    return;
                }
                if (st && hp) {
                    playerState = "st-hp";
                    return;
                }
                if (st && lk) {
                    playerState = "st-lk";
                    return;
                }
                if (st && mk) {
                    playerState = "st-mk";
                    return;
                }
                if (st && hk) {
                    playerState = "st-hk";
                    return;
                }

                if (cr && lp) {
                    playerState = "cr-lp";
                    return;
                }
                if (cr && mp) {
                    playerState = "cr-mp";
                    return;
                }
                if (cr && hp) {
                    playerState = "cr-hp";
                    return;
                }
                if (cr && lk) {
                    playerState = "cr-lk";
                    return;
                }
                if (cr && mk) {
                    playerState = "cr-mk";
                    return;
                }
                if (cr && hk) {
                    playerState = "cr-hk";
                    return;
                }
                if (cr) {
                    playerState = "cr";
                }
                if (((forward && backward) || (!forward && !backward)) && !cr) {
                    playerState = "st";
                }
                if ((forward) && (!cr) && (!backward)) {
                    //if(t.isOK())
                        //getPosition().moveRight();
                    //if(getPositionX() < otherPlayerPosX)
                        playerState = "st-fw";
                    //else
                        //playerState = "st-bw";
                }
                if ((backward) && (!cr) && (!forward)) {
                    //if(t.isOK())
                        //getPosition().moveLeft();
                    //if(getPositionX() < otherPlayerPosX)
                        playerState = "st-bw";
                        
                    //else
                        //playerState = "st-fw";
                }
                if ((backward) && (cr) /*&& (!forward)*/) {
                    //if(t.isOK())
                        //getPosition().moveLeft();
                    //if(getPositionX() < otherPlayerPosX)
                        playerState = "cr-bw";
                    //else
                        //playerState = "st-fw";
                }
                if(nj && forward){
                    playerState = "fj";
                }else if(nj && backward){
                    playerState = "bj";
                }else if(nj){
                    playerState = "nj";
                }
            } else {
                if (!left && !right) {
                    for (int j = 0; j < 3; j++) {
                        char cp = inputs[i][j];
                            if ((cp == 'd') || (cp == 'v')) {
                                right = true;
                                std::cout << "Premier D trouver" << std::endl;
                            }
                            else if ((cp == 'q') || (cp == 'x')) {
                                left = true;
                                right = false;
                                std::cout << "Premier Q trouver" << std::endl;
                            }else if(cp != ' '){
                                left = false;
                                right=false;
                                break;
                            }
                    }
                }else if(!downLeft && !downRight){
                    bool l=false; bool r=false; bool d=false;
                    for(int j= 2; j >= 0 ; j--){
                        char cp = inputs[i][j];
                        if((cp == 'd')||(cp == 'v')){
                            r = true;
                        }else if((cp == 'q')||(cp =='x')){
                            l = true;
                        }
                        if((cp == 's')||(cp == 'c')){
                            d = true;
                            std::cout << "on trouve down" << std::endl;
                        }
                        if(l&&d){
                            downLeft = true;
                            std::cout << "down left est verifié" << std::endl;
                        }else if(r&&d){
                            downRight = true;
                            std::cout << "down right est verifié"<< std::endl;
                        }

                    }
                }
                else if (!down) {
                    for (int j = 0; j < 3; j++) {
                        char cp = inputs[i][j];
                        if ((cp == 's') || (cp == 'c')) {
                            down = true;
                            std::cout << "down trouvé" << std::endl;
                        }
                    }
                }
                if ((down) && (!left && !right)) {
                    if (lp) {
                        playerState = "st-lp";
                        return;
                    }
                    if (mp) {
                        playerState = "st-mp";
                        return;
                    }
                    if (hp) {
                        playerState = "st-hp";
                        return;
                    }
                    if (lk) {
                        playerState = "st-lk";
                        return;
                    }
                    if (mk) {
                        playerState = "st-mk";
                        return;
                    }
                    if (hk) {
                        playerState = "st-hk";
                        return;
                    }
                }
            }
        }
    }
    if(lp||mp||hp||lk||mk||hk)
    {
        if ((right && down && downRight)&&(lp||mp||hp)) {
            playerState = "special1";
            return;
        } else if ((left && down && downLeft)&&(lk||mk||hk)) {
            playerState = "special2";
            return;
        } else {
            if(lp){
                playerState = "st-lp";
                return;
            }
            if(mp){
                playerState = "st-mp";
                return;
            }
            if(hp){
                playerState = "st-hp";
                return;
            }
            if(lk){
                playerState = "st-lk";
                return;
            }
            if(mk){
                playerState = "st-mk";
                return;
            }
            if(hk){
                playerState = "st-hk";
                return;
            }
        }
    }
}


Fighters & Player::getMyFighter() const {
    return * myFighter;
}

int Player::getPositionOnMap() {
    return positionOnMap;
}

void Player::setPositionOnMap(int p) {
    positionOnMap = p;
}

Health& Player::getHealth() {
    return myHealth;
}

void Player::testRegression()
{
    srand(time(NULL));

}

void Player::setBlockStun(int stun) {
    blockStun = stun;
}

int Player::getBlockStun() {
    return blockStun;
}

void Player::blockStunState(Player & otherPlayer) {
    if (blockStun > 0)
    {
        blockStun--;
        if(getPositionX() > otherPlayer.getPositionX())
            setPositionX(getPositionX()+1);
        else
            setPositionX(getPositionX()-1);
    }
}

void Player::hitStunState(Player & otherPlayer) {
    if (hitStun > 0)
    {
        if(playerState.substr(0,2) == "st")
            playerState = "st-hit";
        if(playerState.substr(0,2) == "cr")
            playerState = "cr-hit";
        hitStun--;
        if(getPositionX() > otherPlayer.getPositionX())
            setPositionX(getPositionX()+1);
        else
            setPositionX(getPositionX()-1);
    }
    else
    {
        if(playerState == "st-hit")
            playerState = "st";
        if(playerState == "cr-hit")
            playerState = "cr";
    }
}

void Player::setHitStun(int stun) {
    hitStun = stun;
}