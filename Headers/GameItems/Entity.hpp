#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__
#include"../Vector.hpp"

class EntityType;
class Entity{
    Vector<int> metadata;
    const EntityType* type;
    friend EntityType;
    int id;
    Entity(const EntityType* type,int id):type(type),id(id){}
public:
    Entity();
    void draw();
    void Tick();
    int getId();
    Entity copy(int id);
    const EntityType* getType();
    friend std::ostream& operator<<(std::ostream& os,const Entity& entity);
    friend std::istream& operator>>(std::istream& is,Entity& entity);
    bool operator!=(const Entity& other)const{return !(*this==other);}
    bool operator==(const Entity& other)const{return (type==other.type&&metadata==other.metadata);}
};


#endif // __ENTITY_HPP__
