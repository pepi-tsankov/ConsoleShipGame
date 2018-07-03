#ifndef __LOAD_BUTTON_HPP__
#define __LOAD_BUTTON_HPP__
#include"../BasicEntityTypes.hpp"

class LoadButton:public LivingEntity{
protected:
    virtual int startingMetaLocation();
    virtual int storedMeta();
public:
    LoadButton(int id);
    virtual void KillTick(Entity* entity)const override;
    virtual void drawEntity(Entity* entity)const override;
    virtual void tickEntity(Entity* entity)const override;
    virtual Entity createEntity(int id,Vector<int> metadata=Vector<int>())const override; /// Metadata- x,y,hp, colision damage, side (0-> enemy)
    virtual ~LoadButton();
    virtual Hitbox getColisionBox(Entity* entity)const override;
};






#endif // __LOAD_BUTTON_HPP__
