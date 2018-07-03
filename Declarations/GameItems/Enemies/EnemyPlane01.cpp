#include"../../../Headers/GameItems/Enemies/EnemyPlane01.hpp"
#include"../../../Headers/GameItems/Entity.hpp"
#include"../../../Headers/GUI/Screen.hpp"
#include"../../../Headers/GameItems/System.hpp"
#include"../../../Headers/GameItems/hitbox.hpp"

int EnemyPlane01::startingMetaLocation(){
    return LivingEntity::storedMeta();
}
int EnemyPlane01::storedMeta(){
    return 1;
}

Entity EnemyPlane01::createEntity(int id,Vector<int> metadata)const{
    Entity entity=LivingEntity::createEntity(id,metadata);
    setMeta(&entity,4,0);
    setMeta(&entity,3,2);
    setMeta(&entity,2,5);
    addMeta(&entity,0);
    return entity;
}

void EnemyPlane01::tickEntity(Entity* entity)const{
    if(getMeta(entity,5)==0){
        setMeta(entity,0,getMeta(entity,0)-1);
        setMeta(entity,5,1);
    }else{
        setMeta(entity,5,0);
    }
}

void EnemyPlane01::drawEntity(Entity* entity)const{
    char color[10]={0x0f,0b1000,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f};
    int x=getMeta(entity,0);
    int y=getMeta(entity,1);
    Screen::write(x,y,"/",color,1);
    Screen::write(x,y+1,"-",color+1,1);
    Screen::write(x,y+2,"\\",color,1);
}

EnemyPlane01::~EnemyPlane01(){}

void EnemyPlane01::KillTick(Entity* entity)const{
    if(getMeta(entity,2)<=0){
        System::AddCoins(5);
        System::AddPoints(15);
    }
    if(getMeta(entity,0)<0){
        setMeta(entity,2,0);
    }
    LivingEntity::KillTick(entity);
}

EnemyPlane01::EnemyPlane01(int id):LivingEntity(id){

}

Hitbox EnemyPlane01::getColisionBox(Entity* entity)const{
    return (Hitbox(1,3).copy(getMeta(entity,0),getMeta(entity,1)));
}
