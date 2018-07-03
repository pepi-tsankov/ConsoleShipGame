#ifndef __PLAYER_ROCKET_HPP__
#define __PLAYER_ROCKET_HPP__
#include"../BasicEntityTypes.hpp"

class PlayerRocket:public LivingEntity{
protected:
    virtual int startingMetaLocation();
    virtual int storedMeta();
public:
    PlayerRocket(int id);
    virtual void KillTick(Entity* entity)const override;
    virtual void drawEntity(Entity* entity)const override;
    virtual void tickEntity(Entity* entity)const override;
    virtual Entity createEntity(int id,Vector<int> metadata=Vector<int>())const override; /// Metadata- x,y,hp, colision damage, side (0-> enemy)
    virtual ~PlayerRocket();
    virtual Hitbox getColisionBox(Entity* entity)const override;
};






#endif // __PLAYER_ROCKET_HPP__
