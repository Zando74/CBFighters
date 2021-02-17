#include "CircularBuffer.h"
#include <vector>
#include <iostream>
#include <time.h>

CircularBuffer::CircularBuffer() {
    BUFFER_SIZE = 10;
    frameBuffer1 = {' ',' ',' '};
    frameBuffer2 = {' ',' ',' '};
    for(unsigned int i=0;i<BUFFER_SIZE;i++){
        buffer1.push_back(frameBuffer1);
        buffer2.push_back(frameBuffer2);
    }
}
CircularBuffer::~CircularBuffer() {}


void CircularBuffer::addInput(char input) {
    //removeOldest();
    if((input=='z')||(input=='q')||(input=='s')||(input=='d')||(input=='u')||(input=='i')||(input=='o')||(input=='j')||(input=='k')||(input=='l')){
        if(frameBuffer1[0] == ' '){
            frameBuffer1[0] = input;
        }else if(frameBuffer1[1] == ' '){
            frameBuffer1[1] = input;
        }else{
            frameBuffer1[2] = input;
        }
    }else if((input=='w')||(input=='x')||(input=='c')||(input=='v')||(input=='7')||(input=='8')||(input=='9')||(input=='4')||(input=='5')||(input=='6')){
        if(frameBuffer2[0] == ' '){
            frameBuffer2[0] = input;
        }else if(frameBuffer2[1] == ' '){
            frameBuffer2[1] = input;
        }else{
            frameBuffer2[2] = input;
        }
    }else{
        //buffer1.push_back(' ');
        //buffer2.push_back(' ');
    }
}

void CircularBuffer::addBuffer() {
    removeOldest();
    buffer1.push_back(frameBuffer1);
    buffer2.push_back(frameBuffer2);
    frameBuffer1 = {' ',' ',' '};
    frameBuffer2 = {' ',' ',' '};
}

void CircularBuffer::removeOldest() {
    std::vector<char> tmp;
    tmp.resize(2,0);
    if(buffer1.size() >= BUFFER_SIZE){
        for(unsigned int i=0;i<BUFFER_SIZE;i++){
            tmp = buffer1[i];
            buffer1[i] = buffer1[i+1];
            buffer1[i+1] = tmp;
        }
        buffer1.pop_back();
    }
    if(buffer2.size() >= BUFFER_SIZE){
        for(unsigned int i=0;i<BUFFER_SIZE;i++){
            tmp = buffer2[i];
            buffer2[i] = buffer2[i+1];
            buffer2[i+1] = tmp;
        }
        buffer2.pop_back();
    }
}

void CircularBuffer::saveToList(std::vector<std::vector<char>> &inputList,char who)
{
    if(who == '0'){
        inputList = buffer1;
    }else{
        inputList = buffer2;
    }
}


void CircularBuffer::testPrintbuffer(){
    std::cout << "BufferFrame 1 content :" << std::endl;
    for(unsigned int i=0;i<frameBuffer1.size();i++){
        std::cout << frameBuffer1[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Buffer 2 content :" << std::endl;
    for(unsigned int i=0;i<frameBuffer2.size();i++){
        std::cout << frameBuffer2[i] << " ";
    }
    std::cout << std::endl;
}

void CircularBuffer::testPrintBufferGlobal(){
    std::cout << "Buffer of Player 1 content : " << std::endl;
    for(unsigned int i=0;i<BUFFER_SIZE;i++){
        std::cout << "[" << buffer1[i][0] << "|" << buffer1[i][1] << "|" << buffer1[i][2] << "]" << " ";
    }
    std::cout << std::endl;
    std::cout << "Buffer of Player 2 content : " << std::endl;
    for(unsigned int i=0;i<BUFFER_SIZE;i++){
        std::cout << "[" << buffer2[i][0] << "|" << buffer2[i][1] << "|" << buffer2[i][2] << "]" << " ";
    }
    std::cout << std::endl;
}

void CircularBuffer::testRegression(){
    srand(time(NULL));
    for(int i=0;i<100000;i++){
        char RandomChar = rand() % 255;
        addInput(RandomChar);
        saveToList(buffer1,'0');
        saveToList(buffer2,'1');
        if(i%3 == 0){
            addBuffer();
        }
        testPrintBufferGlobal();
    }
}