#include"../../../Headers/GameItems/Enemies/DeathMsg.hpp"
#include"../../../Headers/GameItems/Entity.hpp"
#include"../../../Headers/GUI/Screen.hpp"
#include"../../../Headers/GameItems/System.hpp"
#include"../../../Headers/GameItems/hitbox.hpp"

int DeathMsg::startingMetaLocation(){
    return LivingEntity::storedMeta();
}
int DeathMsg::storedMeta(){
    return 0;
}

Entity DeathMsg::createEntity(int id,Vector<int> metadata)const{
    Entity entity=LivingEntity::createEntity(id,metadata);
    setMeta(&entity,4,0);
    setMeta(&entity,3,1);
    setMeta(&entity,2,1);
    return entity;
}

void DeathMsg::tickEntity(Entity* entity)const{

}

void DeathMsg::drawEntity(Entity* entity)const{
    char color[40]={0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f};
    Screen::write(30,13,"/============================\\",color,30);
    Screen::write(30,14,"|You have died.              |",color,30);
    Screen::write(30,15,"|Press Enter to exit to      |",color,30);
    Screen::write(30,16,"|the title screen.           |",color,30);
    Screen::write(30,17,"\\============================/",color,30);
}

DeathMsg::~DeathMsg(){}

void DeathMsg::KillTick(Entity* entity)const{
    if(GetAsyncKeyState(0x0D)){
        System::MainScreen();
    }
}

DeathMsg::DeathMsg(int id):LivingEntity(id){

}

Hitbox DeathMsg::getColisionBox(Entity* entity)const{
    return ((Hitbox(0,0)).copy(0,0));
}
