#include"../../../Headers/GameItems/Friendlies/PlayerExplosion.hpp"
#include"../../../Headers/GameItems/Entity.hpp"
#include"../../../Headers/GUI/Screen.hpp"
#include"../../../Headers/GameItems/System.hpp"
#include"../../../Headers/GameItems/hitbox.hpp"

int PlayerExplosion::startingMetaLocation(){
    return LivingEntity::storedMeta();
}
int PlayerExplosion::storedMeta(){
    return 1;
}

Entity PlayerExplosion::createEntity(int id,Vector<int> metadata)const{
    Entity entity=LivingEntity::createEntity(id,metadata);
    setMeta(&entity,4,1);
    setMeta(&entity,3,50);
    setMeta(&entity,2,1000);
    addMeta(&entity,19);
    return entity;
}

void PlayerExplosion::tickEntity(Entity* entity)const{
    setMeta(entity,5,getMeta(entity,5)-1);
    setMeta(entity,3,System::GetPlayerData(2)*20);
}

void PlayerExplosion::drawEntity(Entity* entity)const{
    int radius=getMeta(entity,5)/5;
    for(int x=-radius;x<=radius;x++){
        for(int y=-radius;y<=radius;y++){
            if(x*x+y*y<=(radius*radius)){
                if(getMeta(entity,5)>=18){
                    Screen::setCell(getMeta(entity,0)+x,getMeta(entity,1)+y,'*',0b00001100);
                }else{
                    Screen::setCell(getMeta(entity,0)+x,getMeta(entity,1)+y,'*',0b00001000);
                }
            }
        }
    }
}

PlayerExplosion::~PlayerExplosion(){}

void PlayerExplosion::KillTick(Entity* entity)const{
    if(getMeta(entity,5)==0){
        setMeta(entity,2,0);
        LivingEntity::KillTick(entity);
    }
}

PlayerExplosion::PlayerExplosion(int id):LivingEntity(id){

}

Hitbox PlayerExplosion::getColisionBox(Entity* entity)const{
    if(getMeta(entity,5)==18){
        Hitbox h(7,7);
        for(int x=-3;x<=3;x++){
            for(int y=-3;y<=3;y++){
                if(((x*x)+(y*y))>9){
                    h.set(x+3,y+3,0);
                }
            }
        }
        return h.copy(getMeta(entity,0)-3,getMeta(entity,1)-3);
    }else{
        return Hitbox(0,0);
    }
}
