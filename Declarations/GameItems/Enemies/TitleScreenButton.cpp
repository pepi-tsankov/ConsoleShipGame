#include"../../../Headers/GameItems/Enemies/TitleScreenButton.hpp"
#include"../../../Headers/GameItems/Entity.hpp"
#include"../../../Headers/GUI/Screen.hpp"
#include"../../../Headers/GameItems/System.hpp"
#include"../../../Headers/GameItems/hitbox.hpp"

int TitleScreenButton::startingMetaLocation(){
    return LivingEntity::storedMeta();
}
int TitleScreenButton::storedMeta(){
    return 0;
}

Entity TitleScreenButton::createEntity(int id,Vector<int> metadata)const{
    Entity entity=LivingEntity::createEntity(id,metadata);
    setMeta(&entity,4,0);
    setMeta(&entity,3,0);
    setMeta(&entity,2,1);
    return entity;
}

void TitleScreenButton::tickEntity(Entity* entity)const{

}

void TitleScreenButton::drawEntity(Entity* entity)const{
    char color[14]={0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f};
    Screen::write(68,21,"/============\\",color,14);
    Screen::write(68,22,"|Title Screen|",color,14);
    Screen::write(68,23,"\\============/",color,14);
}

TitleScreenButton::~TitleScreenButton(){}

void TitleScreenButton::KillTick(Entity* entity)const{
    if((getMeta(entity,2)<=0)){
        System::MainScreen();
    }
}

TitleScreenButton::TitleScreenButton(int id):LivingEntity(id){

}

Hitbox TitleScreenButton::getColisionBox(Entity* entity)const{
    return ((Hitbox(14,3)).copy(68,21));
}
