#include"../../../Headers/GameItems/Enemies/ExitButton.hpp"
#include"../../../Headers/GameItems/Entity.hpp"
#include"../../../Headers/GUI/Screen.hpp"
#include"../../../Headers/GameItems/System.hpp"
#include"../../../Headers/GameItems/hitbox.hpp"

int ExitButton::startingMetaLocation(){
    return LivingEntity::storedMeta();
}
int ExitButton::storedMeta(){
    return 0;
}

Entity ExitButton::createEntity(int id,Vector<int> metadata)const{
    Entity entity=LivingEntity::createEntity(id,metadata);
    setMeta(&entity,4,0);
    setMeta(&entity,3,0);
    setMeta(&entity,2,1);
    return entity;
}

void ExitButton::tickEntity(Entity* entity)const{

}

void ExitButton::drawEntity(Entity* entity)const{
    char color[17]={0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f};
    Screen::write(67,21,"/===============\\",color,17);
    Screen::write(67,22,"|Exit to Desktop|",color,17);
    Screen::write(67,23,"\\===============/",color,17);
}

ExitButton::~ExitButton(){}

void ExitButton::KillTick(Entity* entity)const{
    if((getMeta(entity,2)<=0)){
        System::Exit();
    }
}

ExitButton::ExitButton(int id):LivingEntity(id){

}

Hitbox ExitButton::getColisionBox(Entity* entity)const{
    return ((Hitbox(17,3)).copy(67,21));
}
