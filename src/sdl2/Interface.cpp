//
// Created by constantin on 21/04/2020.
//

#include "Interface.h"
Interface::Interface(){
    std::cout<<"INITIALIZED UI"<<'\n';
}

Interface::Interface(std::vector<Interface_Element> AddVector){

}

Interface::~Interface(){
    for (unsigned int index = 0; index < All_UI_Elem.size(); ++index) {
        delete All_UI_Elem[index];
    }
}


void Interface::update() {
    //std::cout<<"NUM OF UPDATE CALL////////// "<<All_UI_Elem.size()<<"\n";
    if(All_UI_Elem.size() >0){
        for (unsigned int index = 0; index < All_UI_Elem.size(); ++index) {
            All_UI_Elem[index]->update();
        }
    }
}

void Interface::draw() {
    //std::cout<<"NUM OF DRAW CALL////////// "<<All_UI_Elem.size()<<"\n";
    if(All_UI_Elem.size() >0){
        for (unsigned int index = 0; index < All_UI_Elem.size(); ++index) {
            All_UI_Elem[index]->draw();
        }
    }
}

void Interface::addElem(Interface_Element *add) {
    All_UI_Elem.push_back(add);
}