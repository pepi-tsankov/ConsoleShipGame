#ifndef __LEVEL_SPAWNER_02_HPP__
#define __LEVEL_SPAWNER_02_HPP__
#include"../BasicEntityTypes.hpp"

class LevelSpawner02:public LivingEntity{
protected:
    virtual int startingMetaLocation();
    virtual int storedMeta();
public:
    LevelSpawner02(int id);
    virtual void KillTick(Entity* entity)const override;
    virtual void drawEntity(Entity* entity)const override;
    virtual void tickEntity(Entity* entity)const override;
    virtual Entity createEntity(int id,Vector<int> metadata=Vector<int>())const override; /// Metadata- x,y,hp, colision damage, side (0-> enemy)
    virtual ~LevelSpawner02();
    virtual Hitbox getColisionBox(Entity* entity)const override;
};






#endif // __LEVEL_SPAWNER_02_HPP__
