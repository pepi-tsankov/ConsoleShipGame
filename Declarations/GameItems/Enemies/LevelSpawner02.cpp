#include"../../../Headers/GameItems/Enemies/LevelSpawner02.hpp"
#include"../../../Headers/GameItems/Entity.hpp"
#include"../../../Headers/GUI/Screen.hpp"
#include"../../../Headers/GameItems/System.hpp"
#include"../../../Headers/GameItems/hitbox.hpp"

int LevelSpawner02::startingMetaLocation(){
    return LivingEntity::storedMeta();
}
int LevelSpawner02::storedMeta(){
    return 1;
}

Entity LevelSpawner02::createEntity(int id,Vector<int> metadata)const{
    Entity entity=LivingEntity::createEntity(id,metadata);
    setMeta(&entity,4,0);
    setMeta(&entity,3,2);
    setMeta(&entity,2,5);
    addMeta(&entity,0);
    return entity;
}

void LevelSpawner02::tickEntity(Entity* entity)const{
    setMeta(entity,1,6+getMeta(entity,1)%19);
    if(getMeta(entity,5)%137==0||getMeta(entity,5)%137==33||getMeta(entity,5)%137==85){
        Vector<int> meta(2);
        meta.pushBack(99);
        meta.pushBack(getMeta(entity,1));
        System::AddEntity(0,12,meta);
    }
    if(getMeta(entity,5)%137==65){
        Vector<int> meta(2);
        meta.pushBack(99);
        meta.pushBack(getMeta(entity,1)%20+4);
        System::AddEntity(0,14,meta);
    }
    setMeta(entity,5,getMeta(entity,5)+1);
}

void LevelSpawner02::drawEntity(Entity* entity)const{
}

LevelSpawner02::~LevelSpawner02(){}

void LevelSpawner02::KillTick(Entity* entity)const{
    if(getMeta(entity,5)>5000){
        setMeta(entity,2,0);
        System::AddEntity(0,16);//spawn boss 1
    }
    LivingEntity::KillTick(entity);
}

LevelSpawner02::LevelSpawner02(int id):LivingEntity(id){

}

Hitbox LevelSpawner02::getColisionBox(Entity* entity)const{
    return Hitbox(0,0);
}
