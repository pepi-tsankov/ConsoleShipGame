#include"../../../Headers/GameItems/Enemies/DmgBuy.hpp"
#include"../../../Headers/GameItems/Entity.hpp"
#include"../../../Headers/GUI/Screen.hpp"
#include"../../../Headers/GameItems/System.hpp"
#include"../../../Headers/GameItems/hitbox.hpp"

int DmgBuy::startingMetaLocation(){
    return LivingEntity::storedMeta();
}
int DmgBuy::storedMeta(){
    return 1;
}

Entity DmgBuy::createEntity(int id,Vector<int> metadata)const{
    Entity entity=LivingEntity::createEntity(id,metadata);
    setMeta(&entity,4,0);
    setMeta(&entity,3,0);
    setMeta(&entity,2,1);
    addMeta(&entity,0);
    return entity;
}

void DmgBuy::tickEntity(Entity* entity)const{

}

void DmgBuy::drawEntity(Entity* entity)const{
    {char color[10]={0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f};
    Screen::write(70,8,"/========\\",color,10);
    Screen::write(70,9,"|+1 DMG - ",color,10);
    Screen::write(70,10,"\\========/",color,10);}
    char color[10]={0x0f,0x0f,0x0f,0b1110,0b1100,0b1100,0b1100,0b1001,0b1001};
    Screen::write(90,9,"o",color+3,1);
    int coins=System::GetPlayerData(2)*30;
    for(int i=0;coins>0||i==0;++i,coins/=10){
        Screen::setCell(89-i,9,'0'+coins%10,0b0111);
    }
}

DmgBuy::~DmgBuy(){}

void DmgBuy::KillTick(Entity* entity)const{
    if(getMeta(entity,2)<=0&&((System::GetPlayerData(2)*30)<=System::GetCoins())){
        if(getMeta(entity,5)){
            setMeta(entity,2,1);
            setMeta(entity,5,getMeta(entity,5)-1);
            return;
        }
        setMeta(entity,5,5);
        System::AddCoins(-(System::GetPlayerData(2)*30));
        System::AddPlayerData(2,1);
        setMeta(entity,2,1);
    }
    if(!System::GetPlayerData(5)){
        setMeta(entity,2,0);
        LivingEntity::KillTick(entity);
    }
}

DmgBuy::DmgBuy(int id):LivingEntity(id){

}

Hitbox DmgBuy::getColisionBox(Entity* entity)const{
    return ((Hitbox(1,3)).copy(70,8));
}
