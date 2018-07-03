#ifndef __HEALTH_REDUCED_HPP__
#define __HEALTH_REDUCED_HPP__
#include"../BasicEntityTypes.hpp"

class HealthReduced:public LivingEntity{
protected:
    virtual int startingMetaLocation();
    virtual int storedMeta();
public:
    HealthReduced(int id);
    virtual void KillTick(Entity* entity)const override;
    virtual void drawEntity(Entity* entity)const override;
    virtual void tickEntity(Entity* entity)const override;
    virtual Entity createEntity(int id,Vector<int> metadata=Vector<int>())const override; /// Metadata- x,y,hp, colision damage, side (0-> enemy)
    virtual ~HealthReduced();
    virtual Hitbox getColisionBox(Entity* entity)const override;
};






#endif // __HEALTH_REDUCED_HPP__
