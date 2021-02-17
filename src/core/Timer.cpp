//
// Created by zando on 26/02/2020.
//

#include "Timer.h"
#include <chrono>
#include <iostream>

using namespace std;
using namespace chrono;

using frame = duration<int32_t, ratio<1, 60>>;
using ms = duration<float, milli>;

Timer::Timer() {
    fpsTimer = steady_clock::now();
}
Timer::~Timer()  {}

void Timer::updateFrame()
{
    FPS = duration_cast<frame>(steady_clock::now() - fpsTimer);
}

bool Timer::isOK()
{
    updateFrame();
    if(FPS.count() >= 1){
        fpsTimer = steady_clock::now();
        return true;
    }
    return false;
}

void Timer::countFrameIn3Sec()
{
    int i=0;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    end = std::chrono::system_clock::now();
    while( std::chrono::duration_cast<std::chrono::seconds>(end-start).count() < 3.0)
    {
        end = std::chrono::system_clock::now();
        if(isOK()){
            i++;
            cout << "LastFrame: " << duration_cast<ms>(FPS).count() << endl;
            cout << "Frame number : " << i << endl;
        }
    }
}

void Timer::testRegression()
{
    int i=0;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    end = std::chrono::system_clock::now();
    while( std::chrono::duration_cast<std::chrono::seconds>(end-start).count() < 10.0)
    {
        end = std::chrono::system_clock::now();
        if(isOK()){
            i++;
            cout << "LastFrame: " << duration_cast<ms>(FPS).count() << endl;
            cout << "Frame number : " << i << endl;
            cout << "Numbers of second : " <<std::chrono::duration_cast<std::chrono::seconds>(end-start).count() << std::endl;
        }
    }
}