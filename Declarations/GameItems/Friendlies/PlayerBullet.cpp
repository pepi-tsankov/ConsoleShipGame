#include"../../../Headers/GameItems/Friendlies/PlayerBullet.hpp"
#include"../../../Headers/GameItems/Entity.hpp"
#include"../../../Headers/GUI/Screen.hpp"
#include"../../../Headers/GameItems/System.hpp"
#include"../../../Headers/GameItems/hitbox.hpp"

int PlayerBullet::startingMetaLocation(){
    return LivingEntity::storedMeta();
}
int PlayerBullet::storedMeta(){
    return 0;
}

Entity PlayerBullet::createEntity(int id,Vector<int> metadata)const{
    Entity entity=LivingEntity::createEntity(id,metadata);
    setMeta(&entity,4,1);
    setMeta(&entity,3,3);
    setMeta(&entity,2,1);
    return entity;
}

void PlayerBullet::tickEntity(Entity* entity)const{
    setMeta(entity,0,getMeta(entity,0)+2);
}

void PlayerBullet::drawEntity(Entity* entity)const{
    Screen::setCell(getMeta(entity,0),getMeta(entity,1),'-',0b00000111);
}

PlayerBullet::~PlayerBullet(){}

void PlayerBullet::KillTick(Entity* entity)const{
    if((getMeta(entity,0)>=99)){
        setMeta(entity,2,0);
    }
    LivingEntity::KillTick(entity);
}

PlayerBullet::PlayerBullet(int id):LivingEntity(id){

}

Hitbox PlayerBullet::getColisionBox(Entity* entity)const{
    return Hitbox(3,1).copy(getMeta(entity,0)-1,getMeta(entity,1));
}
