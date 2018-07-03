#include"../../../Headers/GameItems/Enemies/StartButton.hpp"
#include"../../../Headers/GameItems/Entity.hpp"
#include"../../../Headers/GUI/Screen.hpp"
#include"../../../Headers/GameItems/System.hpp"
#include"../../../Headers/GameItems/hitbox.hpp"

int StartButton::startingMetaLocation(){
    return LivingEntity::storedMeta();
}
int StartButton::storedMeta(){
    return 0;
}

Entity StartButton::createEntity(int id,Vector<int> metadata)const{
    Entity entity=LivingEntity::createEntity(id,metadata);
    setMeta(&entity,4,0);
    setMeta(&entity,3,0);
    setMeta(&entity,2,1);
    return entity;
}

void StartButton::tickEntity(Entity* entity)const{

}

void StartButton::drawEntity(Entity* entity)const{
    char color[10]={0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f};
    Screen::write(70,6,"/========\\",color,10);
    Screen::write(70,7,"|New Game|",color,10);
    Screen::write(70,8,"\\========/",color,10);
}

StartButton::~StartButton(){}

void StartButton::KillTick(Entity* entity)const{
    if((getMeta(entity,2)<=0)){
        System::New();
    }
}

StartButton::StartButton(int id):LivingEntity(id){

}

Hitbox StartButton::getColisionBox(Entity* entity)const{
    return ((Hitbox(10,3)).copy(70,6));
}
