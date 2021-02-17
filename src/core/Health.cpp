//
// Created by constantin on 21/04/2020.
//

#include "Health.h"
#include <iostream>

Health::Health() {
    Current=150;
    Max=150;
}

Health::~Health() {

}

int Health::getCurrent() {
    return Current;
}

void Health::takeDamage(int dmg, int seed) {
    std::cout<<"                         TOOK DAMAGES"<<'\n';
    Current -= dmg;
    if(getCurrent() <0) Current =0;
}