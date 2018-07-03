#include"../../../Headers/GameItems/Enemies/SaveButton.hpp"
#include"../../../Headers/GameItems/Entity.hpp"
#include"../../../Headers/GUI/Screen.hpp"
#include"../../../Headers/GameItems/System.hpp"
#include"../../../Headers/GameItems/hitbox.hpp"

int SaveButton::startingMetaLocation(){
    return LivingEntity::storedMeta();
}
int SaveButton::storedMeta(){
    return 0;
}

Entity SaveButton::createEntity(int id,Vector<int> metadata)const{
    Entity entity=LivingEntity::createEntity(id,metadata);
    setMeta(&entity,4,0);
    setMeta(&entity,3,1);
    setMeta(&entity,2,1);
    return entity;
}

void SaveButton::tickEntity(Entity* entity)const{

}

void SaveButton::drawEntity(Entity* entity)const{
    char color[11]={0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f};
    Screen::write(70,6,"/=========\\",color,11);
    Screen::write(70,7,"|Save Game|",color,11);
    Screen::write(70,8,"\\=========/",color,11);
}

SaveButton::~SaveButton(){}

void SaveButton::KillTick(Entity* entity)const{
    if((getMeta(entity,2)<=0)){
        System::Save();
    }
}

SaveButton::SaveButton(int id):LivingEntity(id){

}

Hitbox SaveButton::getColisionBox(Entity* entity)const{
    return ((Hitbox(11,3)).copy(70,6));
}
