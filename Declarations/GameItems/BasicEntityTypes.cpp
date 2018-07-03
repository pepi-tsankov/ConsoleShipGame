#include"../../Headers/GameItems/BasicEntityTypes.hpp"
#include"../../Headers/Vector.hpp"
#include"../../Headers/GameItems/Entity.hpp"
#include"../../Headers/GameItems/System.hpp"

void EntityType::addMeta(Entity* entity,int data)const{
    entity->metadata.pushBack(data);
}

int EntityType::getMeta(Entity* entity,int position)const{
    return entity->metadata[position];
}

void EntityType::setMeta(Entity* entity,int position,int data)const{
    entity->metadata[position]=data;
}

int EntityType::startingMetaLocation(){
    return 0;
}

int EntityType::storedMeta(){
    return 0;
}

EntityType::~EntityType(){
}

Entity EntityType::createEntity(int id,Vector<int> metadata)const{
    return Entity(this,id);
}

void EntityType::WriteId(std::ostream& os)const{
    os<<id<<std::endl;
}


//// LIVING Entity

int LivingEntity::startingMetaLocation(){
    return 0;
}

int LivingEntity::storedMeta(){
    return 5;
}

void LivingEntity::damage(Entity* entity,int dmg)const{
    setMeta(entity,2,getMeta(entity,2)-dmg);
}

Entity LivingEntity::createEntity(int id,Vector<int> metadata)const{
    Entity entity=EntityType::createEntity(id,metadata);
    for(int i=0;i<5;i++){
        if(metadata.getSize()>i){
            EntityType::addMeta(&entity,metadata[i]);
        }else{
            EntityType::addMeta(&entity,0);
        }
    }
    return entity;
}

LivingEntity::~LivingEntity(){

}

void LivingEntity::KillTick(Entity* entity)const{
    if(getMeta(entity,2)<=0){
        if(getMeta(entity,4)==1){
            System::RemoveEntity(1,entity->getId());
        }else{
            System::RemoveEntity(0,entity->getId());
        }
    }
}

int LivingEntity::getColisionDamage(Entity* entity)const{
    return getMeta(entity,3);
}
