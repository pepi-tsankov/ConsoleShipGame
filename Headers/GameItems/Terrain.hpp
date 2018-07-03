#ifndef __TERRAIN_HPP__
#define __TERRAIN_HPP__
#include<istream>
#include"Entity.hpp"
#include"../Vector.hpp"
#include"BasicEntityTypes.hpp"

class Terrain:public EntityType{
    virtual int startingMetaLocation();
    virtual int storedMeta();
public:
    Terrain(int id):EntityType(id){}
    virtual void drawEntity(Entity* entity)const;
    virtual void tickEntity(Entity* entity)const;
    virtual Entity createEntity(int id,Vector<int> metadata=Vector<int>())const;
    virtual ~Terrain(){}

};






#endif // __TERRAIN_HPP__
