#ifndef __ENEMY_BOSS_01_HPP__
#define __ENEMY_BOSS_01_HPP__
#include"../BasicEntityTypes.hpp"
#include"../hitbox.hpp"

class EnemyBoss01:public LivingEntity{
    Hitbox hBox;
protected:
    virtual int startingMetaLocation();
    virtual int storedMeta();
public:
    EnemyBoss01(int id);
    virtual void KillTick(Entity* entity)const override;
    virtual void drawEntity(Entity* entity)const override;
    virtual void tickEntity(Entity* entity)const override;
    virtual Entity createEntity(int id,Vector<int> metadata=Vector<int>())const override; /// Metadata- x,y,hp, colision damage, side (0-> enemy)
    virtual ~EnemyBoss01();
    virtual Hitbox getColisionBox(Entity* entity)const override;
};






#endif // __ENEMY_BOSS_01_HPP__
