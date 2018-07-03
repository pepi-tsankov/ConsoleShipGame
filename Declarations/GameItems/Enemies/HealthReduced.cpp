#include"../../../Headers/GameItems/Enemies/HealthReduced.hpp"
#include"../../../Headers/GameItems/Entity.hpp"
#include"../../../Headers/GUI/Screen.hpp"
#include"../../../Headers/GameItems/System.hpp"
#include"../../../Headers/GameItems/hitbox.hpp"

int HealthReduced::startingMetaLocation(){
    return LivingEntity::storedMeta();
}
int HealthReduced::storedMeta(){
    return 0;
}

Entity HealthReduced::createEntity(int id,Vector<int> metadata)const{
    Entity entity=LivingEntity::createEntity(id,metadata);
    setMeta(&entity,4,0);
    setMeta(&entity,3,0);
    setMeta(&entity,2,1);
    addMeta(&entity,0);
    return entity;
}

void HealthReduced::tickEntity(Entity* entity)const{

}

void HealthReduced::drawEntity(Entity* entity)const{
    {char color[10]={0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f};
    Screen::write(70,16,"/========\\",color,10);
    Screen::write(70,17,"|+15 HP - ",color,10);
    Screen::write(70,18,"\\========/",color,10);}
    char color[10]={0x0f,0x0f,0x0f,0b1110,0b1100,0b1100,0b1100,0b1001,0b1001};
    Screen::write(90,17,"o",color+3,1);
    int coins=180;
    for(int i=0;coins>0||i==0;++i,coins/=10){
        Screen::setCell(89-i,17,'0'+coins%10,0b0111);
    }
}

HealthReduced::~HealthReduced(){}

void HealthReduced::KillTick(Entity* entity)const{
    if(getMeta(entity,2)<=0&&((180)<=System::GetCoins())){
        if(getMeta(entity,5)){
            setMeta(entity,2,1);
            setMeta(entity,5,getMeta(entity,5)-1);
            return;
        }
        setMeta(entity,5,5);
        System::AddCoins(-(180));
        System::AddPlayerData(4,15);
    }
    setMeta(entity,2,1);
    if(!System::GetPlayerData(5)){
        setMeta(entity,2,0);
        LivingEntity::KillTick(entity);
    }
}

HealthReduced::HealthReduced(int id):LivingEntity(id){

}

Hitbox HealthReduced::getColisionBox(Entity* entity)const{
    return ((Hitbox(1,3)).copy(70,16));
}
