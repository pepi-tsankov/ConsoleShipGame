#include"../../../Headers/GameItems/Friendlies/Helper.hpp"
#include"../../../Headers/GUI/Screen.hpp"
#include"../../../Headers/GameItems/System.hpp"

int Helper::startingMetaLocation(){
    return LivingEntity::storedMeta();
}

int Helper::storedMeta(){
    return 1;
}

Helper::Helper(int id):LivingEntity(id),hBox(2,3),dObj(2,3){
    dObj.setAt(0,0,0x0F,'\\');
    dObj.setAt(0,1,0b00001100,'=');dObj.setAt(1,1,0x0F,'>');
    dObj.setAt(0,2,0x0F,'/');
    hBox.set(1,0,0);
    hBox.set(1,2,0);
}

void Helper::drawEntity(Entity* entity)const{
    int x=getMeta(entity,0);
    int y=getMeta(entity,1);
    dObj.draw(x,y);
}

void Helper::tickEntity(Entity* entity)const{
    if(System::GetPlayerData(5)) return;
    int movement_meta=getMeta(entity,5);
    setMeta(entity,5,getMeta(entity,5)+1);
    setMeta(entity,1,getMeta(entity,1)+((1-((movement_meta%90)/45))?1:(-1))*(movement_meta%3/2));
    if(getMeta(entity,7)==0){
        Vector<int> meta(2);
        meta.pushBack(getMeta(entity,0)+1);
        meta.pushBack(getMeta(entity,1)+1);
        System::AddEntity(1,2,meta);
        setMeta(entity,7,40);
    }else{
        setMeta(entity,7,getMeta(entity,7)-1);
    }
}

Entity Helper::createEntity(int id,Vector<int> metatada)const{
    Entity pl=LivingEntity::createEntity(id,metatada);
    for(int i=5;i<8;i++){
        if(metatada.getSize()>i){
            addMeta(&pl,metatada[i]);
        }else{
            addMeta(&pl,0);
        }
    }
    if(metatada.getSize()<2){
        setMeta(&pl,0,3);
        setMeta(&pl,1,5);
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

Hitbox Helper::getColisionBox(Entity* pl)const{
    int x=getMeta(pl,0);
    int y=getMeta(pl,1);
    return hBox.copy(x,y);
}

Helper::~Helper(){}

void Helper::KillTick(Entity* entity)const{
    if(getMeta(entity,2)<=0){
        Vector<int> meta(2);
        meta.pushBack(getMeta(entity,0));
        meta.pushBack(getMeta(entity,1));
        System::AddEntity(0,4,meta);
    }
    LivingEntity::KillTick(entity);
}
