#include"../../../Headers/GameItems/Enemies/CDbuy.hpp"
#include"../../../Headers/GameItems/Entity.hpp"
#include"../../../Headers/GUI/Screen.hpp"
#include"../../../Headers/GameItems/System.hpp"
#include"../../../Headers/GameItems/hitbox.hpp"

int CDbuy::startingMetaLocation(){
    return LivingEntity::storedMeta();
}
int CDbuy::storedMeta(){
    return 0;
}

Entity CDbuy::createEntity(int id,Vector<int> metadata)const{
    Entity entity=LivingEntity::createEntity(id,metadata);
    setMeta(&entity,4,0);
    setMeta(&entity,3,0);
    setMeta(&entity,2,1);
    addMeta(&entity,0);
    return entity;
}

void CDbuy::tickEntity(Entity* entity)const{

}

void CDbuy::drawEntity(Entity* entity)const{
    {char color[10]={0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f};
    Screen::write(70,4,"/========\\",color,10);
    Screen::write(70,5,"|+1 CDR - ",color,10);
    Screen::write(70,6,"\\========/",color,10);}
    char color[10]={0x0f,0x0f,0x0f,0b1110,0b1100,0b1100,0b1100,0b1001,0b1001};
    Screen::write(90,5,"o",color+3,1);
    int coins=System::GetPlayerData(3)*30;
    for(int i=0;coins>0||i==0;++i,coins/=10){
        Screen::setCell(89-i,5,'0'+coins%10,0b0111);
    }
}

CDbuy::~CDbuy(){}

void CDbuy::KillTick(Entity* entity)const{
    if(getMeta(entity,2)<=0&&((System::GetPlayerData(3)*30)<=System::GetCoins())){
        if(getMeta(entity,5)){
            setMeta(entity,2,1);
            setMeta(entity,5,getMeta(entity,5)-1);
            return;
        }
        setMeta(entity,5,5);
        System::AddCoins(-(System::GetPlayerData(3)*30));
        System::AddPlayerData(3,1);
        setMeta(entity,2,1);
    }
    if(!System::GetPlayerData(5)){
        setMeta(entity,2,0);
        LivingEntity::KillTick(entity);
    }
}

CDbuy::CDbuy(int id):LivingEntity(id){

}

Hitbox CDbuy::getColisionBox(Entity* entity)const{
    return ((Hitbox(1,3)).copy(70,4));
}
