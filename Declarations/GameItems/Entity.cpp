#include"../../Headers/GameItems/BasicEntityTypes.hpp"
#include"../../Headers/GameItems/Entity.hpp"
#include"../../Headers/Vector.hpp"
#include"../../Headers/GameItems/System.hpp"

void Entity::draw(){
    type->drawEntity(this);
}

void Entity::Tick(){
    type->tickEntity(this);
}

int Entity::getId(){
    return id;
}

std::ostream& operator<<(std::ostream& os,const Entity& entity){
    entity.type->WriteId(os);
    os<<entity.id<<std::endl;
    os<<entity.metadata<<std::endl;
    return os;
}

std::istream& operator>>(std::istream& is,Entity& entity){
    int typeId;
    is>>typeId;
    //System::Log()<<"read entity ; type:"<<typeId<<std::endl;
    entity.type=System::getType(typeId);
    is>>entity.id>>entity.metadata;
    return is;
}

Entity::Entity(){}

const EntityType* Entity::getType(){
    return type;
}

Entity Entity::copy(int id){
    Entity e=*this;
    e.id=id;
    return e;
}
