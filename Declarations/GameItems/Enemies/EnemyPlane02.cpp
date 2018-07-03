#include"../../../Headers/GameItems/Enemies/EnemyPlane02.hpp"
#include"../../../Headers/GameItems/Entity.hpp"
#include"../../../Headers/GUI/Screen.hpp"
#include"../../../Headers/GameItems/System.hpp"
#include"../../../Headers/GameItems/hitbox.hpp"

int EnemyPlane02::startingMetaLocation(){
    return LivingEntity::storedMeta();
}
int EnemyPlane02::storedMeta(){
    return 2;
}

Entity EnemyPlane02::createEntity(int id,Vector<int> metadata)const{
    Entity entity=LivingEntity::createEntity(id,metadata);
    setMeta(&entity,4,0);
    setMeta(&entity,3,2);
    setMeta(&entity,2,5);
    addMeta(&entity,0);
    addMeta(&entity,0);
    return entity;
}

void EnemyPlane02::tickEntity(Entity* entity)const{
    if(getMeta(entity,5)==0){
        setMeta(entity,0,getMeta(entity,0)-1);
        setMeta(entity,5,2);
    }else{
        setMeta(entity,5,getMeta(entity,5)-1);
    }
    if(getMeta(entity,6)%72==24){
        setMeta(entity,1,getMeta(entity,1)-1);
    }
    if(getMeta(entity,6)%72==55){
        setMeta(entity,1,getMeta(entity,1)+1);
    }
    if(getMeta(entity,6)%50==3){
        Vector<int> meta(2);
        meta.pushBack(getMeta(entity,0)-1);
        meta.pushBack(getMeta(entity,1));
        System::AddEntity(0,15,meta);
        meta[1]=meta[1]+4;
        System::AddEntity(0,15,meta);
    }
    setMeta(entity,6,getMeta(entity,6)+1);
}

void EnemyPlane02::drawEntity(Entity* entity)const{
    char color[10]={0x0f,0x0f,0b0100,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f};
    int x=getMeta(entity,0);
    int y=getMeta(entity,1);
    Screen::write(x,y," /",color,2);
    Screen::write(x,y+1,"/#",color+1,2);
    Screen::write(x,y+2,"==",color,2);
    Screen::write(x,y+3,"\\#",color+1,2);
    Screen::write(x,y+4," \\",color,2);
}

EnemyPlane02::~EnemyPlane02(){}

void EnemyPlane02::KillTick(Entity* entity)const{
    if(getMeta(entity,2)<=0){
        System::AddCoins(10);
        System::AddPoints(30);
    }
    if(getMeta(entity,0)<0){
        setMeta(entity,2,0);
    }
    LivingEntity::KillTick(entity);
}

EnemyPlane02::EnemyPlane02(int id):LivingEntity(id),hBox(2,5){
    hBox.set(0,0,0);
    hBox.set(0,4,0);
}

Hitbox EnemyPlane02::getColisionBox(Entity* entity)const{
    return hBox.copy(getMeta(entity,0),getMeta(entity,1));
}
