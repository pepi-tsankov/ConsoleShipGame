#include"../../../Headers/GameItems/Enemies/Help.hpp"
#include"../../../Headers/GameItems/Entity.hpp"
#include"../../../Headers/GUI/Screen.hpp"
#include"../../../Headers/GameItems/System.hpp"
#include"../../../Headers/GameItems/hitbox.hpp"

int Help::startingMetaLocation(){
    return LivingEntity::storedMeta();
}
int Help::storedMeta(){
    return 0;
}

Entity Help::createEntity(int id,Vector<int> metadata)const{
    Entity entity=LivingEntity::createEntity(id,metadata);
    setMeta(&entity,4,0);
    setMeta(&entity,3,1);
    setMeta(&entity,2,1);
    return entity;
}

void Help::tickEntity(Entity* entity)const{

}

void Help::drawEntity(Entity* entity)const{
    char color[40]={0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f};
    Screen::write(30,5,"/============================\\",color,30);
    Screen::write(30,6,"|Controls:                   |",color,30);
    Screen::write(30,7,"|Up arrow-move up            |",color,30);
    Screen::write(30,8,"|Down arrow-move down        |",color,30);
    Screen::write(30,9,"|Left arrow-move left        |",color,30);
    Screen::write(30,10,"|Right arrow-move right      |",color,30);
    Screen::write(30,11,"|Button A-shoot bullets      |",color,30);
    Screen::write(30,12,"|Button D-shoot rockets      |",color,30);
    Screen::write(30,13,"|============================|",color,30);
    Screen::write(30,14,"|Shoot or crash into buttons |",color,30);
    Screen::write(30,15,"|to select them.             |",color,30);
    Screen::write(30,16,"|============================|",color,30);
    Screen::write(30,17,"|Shoot or crash into         |",color,30);
    Screen::write(30,18,"|enemies to damage them.     |",color,30);
    Screen::write(30,19,"|Getting shot or crashing    |",color,30);
    Screen::write(30,20,"|takes away from your health.|",color,30);
    Screen::write(30,21,"|============================|",color,30);
    Screen::write(30,22,"|Use [Esc] to pause/unpause  |",color,30);
    Screen::write(30,23,"|the game.                   |",color,30);
    Screen::write(30,24,"\\============================/",color,30);
}

Help::~Help(){}

void Help::KillTick(Entity* entity)const{
    LivingEntity::KillTick(entity);
}

Help::Help(int id):LivingEntity(id){

}

Hitbox Help::getColisionBox(Entity* entity)const{
    return ((Hitbox(30,20)).copy(30,5));
}
