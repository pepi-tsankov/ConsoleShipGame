#include"../../../Headers/GameItems/Friendlies/Player.hpp"
#include"../../../Headers/GUI/Screen.hpp"
#include"../../../Headers/GameItems/System.hpp"

int Player::startingMetaLocation(){
    return LivingEntity::storedMeta();
}

int Player::storedMeta(){
    return 3;
}

Player::Player(int id):LivingEntity(id),hBox(4,3),dObj(4,3){
    dObj.setAt(0,0,0b00000100,'-');dObj.setAt(1,0,0x0F,'\\');
    dObj.setAt(0,1,0b00001100,'='); dObj.setAt(1,1,0b00000100,'#'); dObj.setAt(2,1,0x0F,'=');dObj.setAt(3,1,0x0F,'>');
    dObj.setAt(0,2,0b00000100,'-');dObj.setAt(1,2,0x0F,'/');
    hBox.set(2,0,0);hBox.set(3,0,0);
    hBox.set(2,2,0);hBox.set(3,2,0);
}

void Player::drawEntity(Entity* entity)const{
    int x=getMeta(entity,0);
    int y=getMeta(entity,1);
    int hp=getMeta(entity,2);
    dObj.draw(x,y);
    if(getMeta(entity,7)>0){
        Screen::setCell(x+1,y,' ',0b00000100);
    }
    if(getMeta(entity,6)>0){
        Screen::setCell(x+1,y+2,' ',0b00000100);
    }
    int i;
    for(i=0;i<hp/5;i++){
        Screen::setCell(i+6,0,'0',0b00001010);
    }
    switch(hp%5){
    case 1:
        Screen::setCell(i+6,0,'u',0b00000100);
        break;
    case 2:
        Screen::setCell(i+6,0,'3',0b00001100);
        break;
    case 3:
        Screen::setCell(i+6,0,'9',0b00000110);
        break;
    case 4:
        Screen::setCell(i+6,0,'8',0b00001110);
        break;
    }
}

void Player::tickEntity(Entity* entity)const{
    int hp=System::GetPlayerData(4);
    if(hp){
        System::AddPlayerData(4,-hp);
        setMeta(entity,2,getMeta(entity,2)+hp);
    }
    int cd=System::GetPlayerData(3);
    if(getMeta(entity,5)==0){
        if(GetAsyncKeyState(VK_UP)&&getMeta(entity,1)>2){
            setMeta(entity,1,getMeta(entity,1)-1);
            setMeta(entity,5,2);
        }
        if(GetAsyncKeyState(VK_DOWN)&&getMeta(entity,1)<25){
            setMeta(entity,1,getMeta(entity,1)+1);
            setMeta(entity,5,2);
        }
        if(GetAsyncKeyState(VK_RIGHT)&&getMeta(entity,0)<96){
            setMeta(entity,0,getMeta(entity,0)+1);
            setMeta(entity,5,2);
        }
        if(GetAsyncKeyState(VK_LEFT)&&getMeta(entity,0)>0){
            setMeta(entity,0,getMeta(entity,0)-1);
            setMeta(entity,5,2);
        }
    }else{
        setMeta(entity,5,getMeta(entity,5)-1);
    }
    if(getMeta(entity,6)==0){
        if(GetAsyncKeyState(0x44)){
            Vector<int> meta(2);
            meta.pushBack(getMeta(entity,0)+2);
            meta.pushBack(getMeta(entity,1)+2);
            System::AddEntity(1,2,meta);
            setMeta(entity,6,360/cd);
        }
    }else{
        GetAsyncKeyState(0x44);
        setMeta(entity,6,getMeta(entity,6)-1);
    }
    if(getMeta(entity,7)==0){
        if(GetAsyncKeyState(0x41)){
            Vector<int> meta(2);
            meta.pushBack(getMeta(entity,0)+2);
            meta.pushBack(getMeta(entity,1));
            System::AddEntity(1,3,meta);
            setMeta(entity,7,40/cd);
        }
    }else{
        GetAsyncKeyState(0x41);
        setMeta(entity,7,getMeta(entity,7)-1);
    }
}

Entity Player::createEntity(int id,Vector<int> metatada)const{
    Entity pl=LivingEntity::createEntity(id,metatada);
    for(int i=5;i<8;i++){
        if(metatada.getSize()>i){
            addMeta(&pl,metatada[i]);
        }else{
            addMeta(&pl,0);
        }
    }
    if(metatada.getSize()<2){
        setMeta(&pl,0,5);
        setMeta(&pl,1,12);
    }
    if(metatada.getSize()<3){
        setMeta(&pl,2,25);
    }
    if(metatada.getSize()<4){
        setMeta(&pl,3,5);
    }
    if(metatada.getSize()<5){
        setMeta(&pl,4,1);
    }
    return pl;
}

Hitbox Player::getColisionBox(Entity* pl)const{
    int x=getMeta(pl,0);
    int y=getMeta(pl,1);
    return hBox.copy(x,y);
}

Player::~Player(){}

void Player::KillTick(Entity* entity)const{
    if(getMeta(entity,2)<=0){
        System::AddEntity(0,11);
    }
    LivingEntity::KillTick(entity);
}
