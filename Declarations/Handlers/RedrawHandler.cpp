#include"../../Headers/Handlers.hpp"
#include"../../Headers/GUI/Screen.hpp"
#include"../../Headers/GameItems/Terrain.hpp"
#include"../../Headers/GameItems/Entity.hpp"
#include"../../Headers/GameItems/System.hpp"

void RedrawHandler(){
    Screen::clearBuffer();
    int rect[4]={0,1,99,1};
    Screen::fill2d(0xCF,'-',rect);
    rect[3]=(rect[1]=28);
    Screen::fill2d(0xCF,'-',rect);
    System::Draw();
    Screen::swapBuffers();
}
