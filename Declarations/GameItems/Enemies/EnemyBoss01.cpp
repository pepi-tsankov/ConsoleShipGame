#include"../../../Headers/GameItems/Enemies/EnemyBoss01.hpp"
#include"../../../Headers/GameItems/Entity.hpp"
#include"../../../Headers/GUI/Screen.hpp"
#include"../../../Headers/GameItems/System.hpp"
#include"../../../Headers/GameItems/hitbox.hpp"

int EnemyBoss01::startingMetaLocation(){
    return LivingEntity::storedMeta();
}
int EnemyBoss01::storedMeta(){
    return 2;
}

Entity EnemyBoss01::createEntity(int id,Vector<int> metadata)const{
    Entity entity=LivingEntity::createEntity(id,metadata);
    setMeta(&entity,4,0);
    setMeta(&entity,3,4);
    setMeta(&entity,2,500);
    addMeta(&entity,0);
    addMeta(&entity,0);
    setMeta(&entity,0,100);
    setMeta(&entity,1,12);
    return entity;
}

void EnemyBoss01::tickEntity(Entity* entity)const{
    if(getMeta(entity,6)<0) return;
    if(getMeta(entity,5)==0){
        if(getMeta(entity,0)>90){
            setMeta(entity,0,getMeta(entity,0)-1);
            setMeta(entity,5,5);
        }
    }else{
        setMeta(entity,5,getMeta(entity,5)-1);
    }
    if(getMeta(entity,6)%400==0){
        Vector<int> meta(2);
        meta.pushBack(99);
        meta.pushBack(21);
        System::AddEntity(0,12,meta);
        meta[1]=7;
        System::AddEntity(0,12,meta);
    }
    if(getMeta(entity,6)%400==6){
        Vector<int> meta(2);
        meta.pushBack(99);
        meta.pushBack(5);
        System::AddEntity(0,12,meta);
        meta[1]=9;
        System::AddEntity(0,12,meta);
        meta[1]=19;
        System::AddEntity(0,12,meta);
        meta[1]=23;
        System::AddEntity(0,12,meta);
    }
    if(getMeta(entity,6)%150==0){
        Vector<int> meta(2);
        meta.pushBack(getMeta(entity,0)-1);
        meta.pushBack(15);
        System::AddEntity(0,15,meta);
    }
    if(getMeta(entity,6)%150==1){
        Vector<int> meta(2);
        meta.pushBack(getMeta(entity,0)-1);
        meta.pushBack(16);
        System::AddEntity(0,15,meta);
        meta[1]=14;
        System::AddEntity(0,15,meta);
    }
    if(getMeta(entity,6)%150==2){
        Vector<int> meta(2);
        meta.pushBack(getMeta(entity,0)-1);
        meta.pushBack(17);
        System::AddEntity(0,15,meta);
        meta[1]=13;
        System::AddEntity(0,15,meta);
    }
    if(getMeta(entity,6)%150==3){
        Vector<int> meta(2);
        meta.pushBack(getMeta(entity,0)-1);
        meta.pushBack(18);
        System::AddEntity(0,15,meta);
        meta[1]=12;
        System::AddEntity(0,15,meta);
    }
    setMeta(entity,6,getMeta(entity,6)+1);
}

void EnemyBoss01::drawEntity(Entity* entity)const{
    if(getMeta(entity,6)<0) return;
    char color[23]={0x0f,0x0f,0b0100,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f};
    int x=getMeta(entity,0);
    int y=getMeta(entity,1);
    Screen::write(x,y," /",color,2);
    Screen::write(x,y+1,"/|",color,2);
    Screen::write(x,y+2,"|#",color+1,2);
    Screen::write(x,y+3,"==",color,2);
    Screen::write(x,y+4,"|#",color+1,2);
    Screen::write(x,y+5,"\\|",color,2);
    Screen::write(x,y+6," \\",color,2);
    Screen::write(20,29,"00000000000000000000",color+3,getMeta(entity,2)/50);
    Screen::setCell(20+getMeta(entity,2)/50,29,'0',0b0100);
}

EnemyBoss01::~EnemyBoss01(){}

void EnemyBoss01::KillTick(Entity* entity)const{
    if(getMeta(entity,6)<0){
        setMeta(entity,6,getMeta(entity,6)-1);
        if(getMeta(entity,6)==-59) System::AddEntity(0,17);
        if(getMeta(entity,6)==-60) LivingEntity::KillTick(entity);
        return;
    }
    if(getMeta(entity,2)<=0){
        Vector<int> meta(2);
        meta.pushBack(getMeta(entity,0)+1);
        meta.pushBack(getMeta(entity,1)+2);
        System::AddEntity(1,4,meta);
        meta[1]=meta[1]+2;
        System::AddEntity(1,4,meta);
        System::AddCoins(250);
        System::AddPoints(400);
        setMeta(entity,6,-1);
    }
}

EnemyBoss01::EnemyBoss01(int id):LivingEntity(id),hBox(2,7){
    hBox.set(0,0,0);
    hBox.set(0,6,0);
}

Hitbox EnemyBoss01::getColisionBox(Entity* entity)const{
    if(getMeta(entity,6)<0) return Hitbox(0,0);
    return hBox.copy(getMeta(entity,0),getMeta(entity,1));
}
