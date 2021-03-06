#ifndef __SHOP_HPP__
#define __SHOP_HPP__
#include"../BasicEntityTypes.hpp"

class Shop:public LivingEntity{
protected:
    virtual int startingMetaLocation();
    virtual int storedMeta();
public:
    Shop(int id);
    virtual void KillTick(Entity* entity)const override;
    virtual void drawEntity(Entity* entity)const override;
    virtual void tickEntity(Entity* entity)const override;
    virtual Entity createEntity(int id,Vector<int> metadata=Vector<int>())const override; /// Metadata- x,y,hp, colision damage, side (0-> enemy)
    virtual ~Shop();
    virtual Hitbox getColisionBox(Entity* entity)const override;
};






#endif // __SHOP_HPP__
