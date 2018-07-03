#ifndef __SAVE_BUTTON_HPP__
#define __SAVE_BUTTON_HPP__
#include"../BasicEntityTypes.hpp"

class SaveButton:public LivingEntity{
protected:
    virtual int startingMetaLocation();
    virtual int storedMeta();
public:
    SaveButton(int id);
    virtual void KillTick(Entity* entity)const override;
    virtual void drawEntity(Entity* entity)const override;
    virtual void tickEntity(Entity* entity)const override;
    virtual Entity createEntity(int id,Vector<int> metadata=Vector<int>())const override; /// Metadata- x,y,hp, colision damage, side (0-> enemy)
    virtual ~SaveButton();
    virtual Hitbox getColisionBox(Entity* entity)const override;
};






#endif // __SAVE_BUTTON_HPP__
