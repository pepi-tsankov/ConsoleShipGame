#ifndef __DEATH_MSG_HPP__
#define __DEATH_MSG_HPP__
#include"../BasicEntityTypes.hpp"

class DeathMsg:public LivingEntity{
protected:
    virtual int startingMetaLocation();
    virtual int storedMeta();
public:
    DeathMsg(int id);
    virtual void KillTick(Entity* entity)const override;
    virtual void drawEntity(Entity* entity)const override;
    virtual void tickEntity(Entity* entity)const override;
    virtual Entity createEntity(int id,Vector<int> metadata=Vector<int>())const override; /// Metadata- x,y,hp, colision damage, side (0-> enemy)
    virtual ~DeathMsg();
    virtual Hitbox getColisionBox(Entity* entity)const override;
};






#endif // __DEATH_MSG_HPP__
