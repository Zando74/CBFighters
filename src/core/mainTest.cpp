#include <iostream>
#include <unistd.h>
#include "CircularBuffer.h"
#include "Fighters.h"
#include "Timer.h"
#include "Movement.h"

void sleepfct()
{
    std::cout.flush();
    sleep(1);
    std::cout << '.';
    std::cout.flush();
    sleep(1);
    std::cout << '.';
    std::cout.flush();
    sleep(1);
    std::cout << '.';
    std::cout.flush();
    sleep(1);
}


int main(void)
{
    CircularBuffer TestCircularBuffer;
    std::string nFighters = "ryu";
    Fighters TestFighters(nFighters);
    Timer TestTimer;
    std::string nMovement = "st-fw";
    std::string nMove = "st-mp";
    Movement TestMovement(nFighters,nMovement);
    Moves TestMove(nFighters,nMove);

    std::cout << "Le test du module CircularBuffer va commencer ";
    sleepfct();
    TestCircularBuffer.testRegression();
    std::cout << "Le test c'est bien passé !" << std::endl;

    std::cout << "Le test du module Fighters va commencer ";
    sleepfct();
    TestFighters.testRegression();
    std::cout << "Le test c'est bien passé !" << std::endl;

    std::cout << "Le test du module Timer va commencer ";
    sleepfct();
    TestTimer.testRegression();
    std::cout << "Le test c'est bien passé !" << std::endl;

    std::cout << "Le test du module Movement va commencer ";
    sleepfct();
    TestMovement.testRegression();
    std::cout << "Le test c'est bien passé !" << std::endl;

    std::cout << "Le test du module Moves va commencer ";
    sleepfct();
    TestMove.testRegression();
    std::cout << "Le test c'est bien passé !" << std::endl;


    return 0;
}