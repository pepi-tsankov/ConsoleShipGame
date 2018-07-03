#include"../../../Headers/GameItems/Enemies/EnemyBullet01.hpp"
#include"../../../Headers/GameItems/Entity.hpp"
#include"../../../Headers/GUI/Screen.hpp"
#include"../../../Headers/GameItems/System.hpp"
#include"../../../Headers/GameItems/hitbox.hpp"

int EnemyBullet01::startingMetaLocation(){
    return LivingEntity::storedMeta();
}
int EnemyBullet01::storedMeta(){
    return 1;
}

Entity EnemyBullet01::createEntity(int id,Vector<int> metadata)const{
    Entity entity=LivingEntity::createEntity(id,metadata);
    setMeta(&entity,4,0);
    setMeta(&entity,3,3);
    setMeta(&entity,2,1);
    return entity;
}

void EnemyBullet01::tickEntity(Entity* entity)const{
    setMeta(entity,0,getMeta(entity,0)-2);
}

void EnemyBullet01::drawEntity(Entity* entity)const{
    char color[10]={0x0f,0b1100,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f};
    int x=getMeta(entity,0);
    int y=getMeta(entity,1);
    Screen::write(x,y,"-",color+1,1);
}

EnemyBullet01::~EnemyBullet01(){}

void EnemyBullet01::KillTick(Entity* entity)const{
    if(getMeta(entity,0)<0){
        setMeta(entity,2,0);
    }
    LivingEntity::KillTick(entity);
}

EnemyBullet01::EnemyBullet01(int id):LivingEntity(id){

}

Hitbox EnemyBullet01::getColisionBox(Entity* entity)const{
    return ((Hitbox(1,1)).copy(getMeta(entity,0),getMeta(entity,1)));
}
