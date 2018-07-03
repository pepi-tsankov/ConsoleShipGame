#include"../../../Headers/GameItems/Enemies/Shop.hpp"
#include"../../../Headers/GameItems/Entity.hpp"
#include"../../../Headers/GUI/Screen.hpp"
#include"../../../Headers/GameItems/System.hpp"
#include"../../../Headers/GameItems/hitbox.hpp"

int Shop::startingMetaLocation(){
    return LivingEntity::storedMeta();
}
int Shop::storedMeta(){
    return 0;
}

Entity Shop::createEntity(int id,Vector<int> metadata)const{
    System::AddPlayerData(5,1);
    System::AddEntity(0,18);
    System::AddEntity(0,19);
    System::AddEntity(0,20);
    System::AddEntity(0,21);
    Entity entity=LivingEntity::createEntity(id,metadata);
    setMeta(&entity,4,0);
    setMeta(&entity,3,0);
    setMeta(&entity,2,1);
    return entity;
}

void Shop::tickEntity(Entity* entity)const{

}

void Shop::drawEntity(Entity* entity)const{
    char color[10]={0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f};
    Screen::write(70,23,"/========\\",color,10);
    Screen::write(70,24,"|Continue|",color,10);
    Screen::write(70,25,"\\========/",color,10);
}

Shop::~Shop(){}

void Shop::KillTick(Entity* entity)const{
    if((getMeta(entity,2)<=0)){
        System::AddPlayerData(5,-1);
        System::AddEntity(0,22);
    }
    LivingEntity::KillTick(entity);
}

Shop::Shop(int id):LivingEntity(id){

}

Hitbox Shop::getColisionBox(Entity* entity)const{
    return ((Hitbox(10,3)).copy(70,23));
}
