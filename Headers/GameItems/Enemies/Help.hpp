#ifndef __HELP_HPP__
#define __HELP_HPP__
#include"../BasicEntityTypes.hpp"

class Help:public LivingEntity{
protected:
    virtual int startingMetaLocation();
    virtual int storedMeta();
public:
    Help(int id);
    virtual void KillTick(Entity* entity)const override;
    virtual void drawEntity(Entity* entity)const override;
    virtual void tickEntity(Entity* entity)const override;
    virtual Entity createEntity(int id,Vector<int> metadata=Vector<int>())const override; /// Metadata- x,y,hp, colision damage, side (0-> enemy)
    virtual ~Help();
    virtual Hitbox getColisionBox(Entity* entity)const override;
};






#endif // __HELP_HPP__
