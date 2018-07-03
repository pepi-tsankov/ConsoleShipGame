#include"../../../Headers/GameItems/Enemies/LoadButton.hpp"
#include"../../../Headers/GameItems/Entity.hpp"
#include"../../../Headers/GUI/Screen.hpp"
#include"../../../Headers/GameItems/System.hpp"
#include"../../../Headers/GameItems/hitbox.hpp"
#include<fstream>

int LoadButton::startingMetaLocation(){
    return LivingEntity::storedMeta();
}
int LoadButton::storedMeta(){
    return 0;
}

Entity LoadButton::createEntity(int id,Vector<int> metadata)const{
    Entity entity=LivingEntity::createEntity(id,metadata);
    setMeta(&entity,4,0);
    setMeta(&entity,3,0);
    setMeta(&entity,2,1);
    return entity;
}

void LoadButton::tickEntity(Entity* entity)const{

}

void LoadButton::drawEntity(Entity* entity)const{
    char color[11]={0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f};
    std::ifstream file("save.bin");
    if(file){
        Screen::write(70,14,"/=========\\",color,11);
        Screen::write(70,15,"|Load Game|",color,11);
        Screen::write(70,16,"\\=========/",color,11);
    }
}

LoadButton::~LoadButton(){}

void LoadButton::KillTick(Entity* entity)const{
    if((getMeta(entity,2)<=0)){
        System::Load();
    }
}

LoadButton::LoadButton(int id):LivingEntity(id){

}

Hitbox LoadButton::getColisionBox(Entity* entity)const{
    std::ifstream file("save.bin");
    if(file){
        return ((Hitbox(11,3)).copy(70,14));
    }
    return Hitbox(0,0).copy(0,0);
}
