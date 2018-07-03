#ifndef __HELPER_HPP__
#define __HELPER_HPP__
#include"../BasicEntityTypes.hpp"
#include"../../GUI/DrawableObject.hpp"
#include"../hitbox.hpp"

class Helper:public LivingEntity{
    Hitbox hBox;
    DrawableObject dObj;
    virtual int startingMetaLocation();
    virtual int storedMeta();
public:
    Helper(int id);
    virtual void KillTick(Entity* entity)const;
    virtual void drawEntity(Entity* entity)const;
    virtual void tickEntity(Entity* entity)const;
    virtual Entity createEntity(int id,Vector<int> metadata=Vector<int>())const; /// Metadata- x,y,hp, colision damage, side | last movement
    virtual ~Helper();
    virtual Hitbox getColisionBox(Entity* entity)const;
};



#endif // __HELPER_HPP__
