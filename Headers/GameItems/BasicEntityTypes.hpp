#ifndef __BASIC_ENTITY_TYPES_HPP__
#define __BASIC_ENTITY_TYPES_HPP__
#include"../Vector.hpp"
class Entity;
class Hitbox;

class EntityType{
    int id;
protected:
    void addMeta(Entity* entity,int data)const;
    int getMeta(Entity* entity,int position)const;
    void setMeta(Entity* entity,int position,int data)const;
    virtual int startingMetaLocation()=0;
    virtual int storedMeta()=0;
public:
    EntityType(int id):id(id){}
    virtual void drawEntity(Entity* entity)const=0;
    virtual void tickEntity(Entity* entity)const=0;
    virtual Entity createEntity(int id,Vector<int> metadata=Vector<int>())const =0;
    virtual ~EntityType();
    void WriteId(std::ostream& os)const;
};

class LivingEntity:public EntityType{
protected:
    virtual int startingMetaLocation();
    virtual int storedMeta();
public:
    LivingEntity(int id):EntityType(id){}
    virtual void KillTick(Entity* entity)const;
    virtual void drawEntity(Entity* entity)const override=0;
    virtual void tickEntity(Entity* entity)const override=0;
    virtual Entity createEntity(int id,Vector<int> metadata=Vector<int>())const override=0; /// Metadata- x,y,hp, colision damage, side (0-> enemy)
    virtual ~LivingEntity();
    virtual Hitbox getColisionBox(Entity* entity)const=0;
    int getColisionDamage(Entity* entity)const;
    void damage(Entity* entity,int dmg)const;
};



#endif // __BASIC_ENTITY_TYPES_HPP__
