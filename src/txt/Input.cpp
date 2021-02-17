#include "Input.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>


Input::Input() {
    input = 0;
}
Input::~Input() {}


char Input::getInput() {
    return input;
}


void Input::listenInput() {

    //system("/bin/stty raw");
    struct termios initial_settings, new_settings;
    tcgetattr(0,&initial_settings);

    new_settings = initial_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_lflag &= ~ISIG;
    new_settings.c_cc[VMIN] = 0;
    new_settings.c_cc[VTIME] = 0;

    tcsetattr(0, TCSANOW, &new_settings);

    input = getchar();

    if((input!='q')&&(input!='d')&&(input!='i')&&(input!='x')&&(input!='v')&&(input!='8')){
        input =' ';
    }
    if(input == 'q')
        input = 'd';
    else if(input =='d')
        input = 'q';

    system("clear");
    //system("/bin/stty cooked");
    tcsetattr(0, TCSANOW, &initial_settings);
}