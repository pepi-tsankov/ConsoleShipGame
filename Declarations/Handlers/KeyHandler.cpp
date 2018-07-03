#include"../../Headers/Handlers.hpp"
#include"../../Headers/GameWrapper.hpp"
#include<windows.h>
#include"../../Headers/GameItems/System.hpp"

void KeyHandler(){
    if(GetAsyncKeyState(VK_ESCAPE)){
        static int num(0);
        if(num==0){
            System::PauseUnpause();
            num=5;
        }else{
            num--;
        }
    }
}
