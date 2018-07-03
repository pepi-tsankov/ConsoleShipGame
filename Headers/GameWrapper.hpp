#ifndef __GAMEWRAPPER_HPP_P__
#define __GAMEWRAPPER_HPP_P__

class GameWrapper{
    static void (*tickHandler)(int);
    static void (*keyHandler)(void);
    static void (*redrawHandler)(void);
    static bool running;
    static float TPS;
    GameWrapper(GameWrapper& gm);
public:
    static void setTps(float tps){TPS=tps;}
    static void exit(){running=false;}
    static void addKeyHandler(void keyHandle(void)){keyHandler=keyHandle;}
    static void addTickHandler(void tickHandle(int)){tickHandler=tickHandle;}
    static void addRedrawHandler(void redrawHandle(void)){redrawHandler=redrawHandle;}
    static void start();
};
#endif // __GAMEWRAPPER_HPP_P__
