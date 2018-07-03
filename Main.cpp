#include"./Headers/GUI/Screen.hpp"
#include"./Headers/Handlers.hpp"
#include"./Headers/GameWrapper.hpp"
#include<iostream>
#include"./Headers/GameItems/BasicEntityTypes.hpp"
#include"./Headers/GameItems/Entity.hpp"
#include"Headers/GameItems/System.hpp"

using namespace std;
int main(){
    System::Setup();
    System::MainScreen();
    GameWrapper::addKeyHandler(KeyHandler);
    GameWrapper::addRedrawHandler(RedrawHandler);
    GameWrapper::addTickHandler(TickHandler);
    GameWrapper::start();
}
