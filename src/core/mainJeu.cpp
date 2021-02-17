#include <iostream>
#include <string>
#include "../txt/Game.h"
#include "../sdl2/Ihm.h"

int main(){
    std::string choose;
    std::cout <<"Tapez  \"txt\" ou \"sdl\" pour jouer" << std::endl;
    std::cin >> choose;
    if(choose == "sdl"){
        Ihm game;
        game.run();
    }else if(choose =="txt"){
        std::string p1 = "ryu";
        std::string p2 = "ryu";
        Game game(p1,p2);
        game.run();
    }else{
        std::cout << "Mot pas reconnu ! sortie du programme" << std::endl;
    }

    return 0;
}
