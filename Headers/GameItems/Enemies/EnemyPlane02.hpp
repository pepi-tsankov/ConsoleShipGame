#ifndef __ENEMY_PLANE_02_HPP__
#define __ENEMY_PLANE_02_HPP__
#include"../BasicEntityTypes.hpp"
#include"../hitbox.hpp"

class EnemyPlane02:public LivingEntity{
    Hitbox hBox;
protected:
    virtual int startingMetaLocation();
    virtual int storedMeta();
public:
    EnemyPlane02(int id);
    virtual void KillTick(Entity* entity)const override;
    virtual void drawEntity(Entity* entity)const override;
    virtual void tickEntity(Entity* entity)const override;
    virtual Entity createEntity(int id,Vector<int> metadata=Vector<int>())const override; /// Metadata- x,y,hp, colision damage, side (0-> enemy)
    virtual ~EnemyPlane02();
    virtual Hitbox getColisionBox(Entity* entity)const override;
};






#endif // __ENEMY_PLANE_02_HPP__
