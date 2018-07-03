#include"../Headers/GameWrapper.hpp"
#include<windows.h>

inline long long milliseconds_now() {
    static LARGE_INTEGER s_frequency;
    static BOOL s_use_qpc = QueryPerformanceFrequency(&s_frequency);
    if (s_use_qpc) {
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        return (1000LL * now.QuadPart) / s_frequency.QuadPart;
    } else {
        return GetTickCount();
    }
}

bool GameWrapper::running=false;
void (*GameWrapper::tickHandler)(int);
void (*GameWrapper::keyHandler)(void);
void (*GameWrapper::redrawHandler)(void);
float GameWrapper::TPS=30;

void GameWrapper::start(){
    GameWrapper::running=true;
    int time=milliseconds_now();
    int tick=0;
    while(running){
        keyHandler();
        tickHandler(tick);
        redrawHandler();

        while(((1000.0f/TPS)-milliseconds_now()+time)>0);
        time=milliseconds_now();
        tick++;
    }
}
