#ifndef __PLAYER_EXPLOSION_HPP__
#define __PLAYER_EXPLOSION_HPP__
#include"../BasicEntityTypes.hpp"

class PlayerExplosion:public LivingEntity{
protected:
    virtual int startingMetaLocation();
    virtual int storedMeta();
public:
    PlayerExplosion(int id);
    virtual void KillTick(Entity* entity)const override;
    virtual void drawEntity(Entity* entity)const override;
    virtual void tickEntity(Entity* entity)const override;
    virtual Entity createEntity(int id,Vector<int> metadata=Vector<int>())const override; /// Metadata- x,y,hp, colision damage, side (0-> enemy)
    virtual ~PlayerExplosion();
    virtual Hitbox getColisionBox(Entity* entity)const override;
};






#endif // __PLAYER_EXPLOSION_HPP__
