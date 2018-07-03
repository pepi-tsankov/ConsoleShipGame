#include"../../../Headers/GameItems/Friendlies/PlayerRocket.hpp"
#include"../../../Headers/GameItems/Entity.hpp"
#include"../../../Headers/GUI/Screen.hpp"
#include"../../../Headers/GameItems/System.hpp"
#include"../../../Headers/GameItems/hitbox.hpp"

int PlayerRocket::startingMetaLocation(){
    return LivingEntity::storedMeta();
}
int PlayerRocket::storedMeta(){
    return 0;
}

Entity PlayerRocket::createEntity(int id,Vector<int> metadata)const{
    Entity entity=LivingEntity::createEntity(id,metadata);
    setMeta(&entity,4,1);
    setMeta(&entity,3,5);
    setMeta(&entity,2,1);
    addMeta(&entity,0);
    return entity;
}

void PlayerRocket::tickEntity(Entity* entity)const{
    setMeta(entity,0,getMeta(entity,0)+1);
    setMeta(entity,3,System::GetPlayerData(2)*2);
}

void PlayerRocket::drawEntity(Entity* entity)const{
    Screen::setCell(getMeta(entity,0),getMeta(entity,1),'+',0b00001100);
}

PlayerRocket::~PlayerRocket(){}

void PlayerRocket::KillTick(Entity* entity)const{
    if(getMeta(entity,2)<=0||(getMeta(entity,0)>=99)){
        setMeta(entity,2,0);
        Vector<int> meta(2);
        meta.pushBack(getMeta(entity,0));
        meta.pushBack(getMeta(entity,1));
        System::AddEntity(1,4,meta);
    }
    LivingEntity::KillTick(entity);
}

PlayerRocket::PlayerRocket(int id):LivingEntity(id){

}

Hitbox PlayerRocket::getColisionBox(Entity* entity)const{
    return Hitbox(2,1).copy(getMeta(entity,0)-1,getMeta(entity,1));
}
