#ifndef __SYSTEM_HPP__
#define __SYSTEM_HPP__
#include"../Vector.hpp"
#include"Entity.hpp"
class EntityType;

class System{
    Vector<EntityType*> types;
    Vector<Entity> friendlies;
    Vector<Entity> foes;
    Entity background;
    void clean();
    int state; // 0- in-game 1- in title screen 2- in pause screen
    System();
    ~System();
    bool continue_;
    static System& getInstance();
    Vector<int> AddPlayerDat; // points ; coins ; dmg ; cooldown ; hp ; shop meta
public:
    static void AddPoints(int points){getInstance().AddPlayerDat[0]+=points;}
    static void AddCoins(int coins){getInstance().AddPlayerDat[1]+=coins;}
    static int GetCoins(){return getInstance().AddPlayerDat[1];}
    static void AddPlayerData(int loc,int ammount){getInstance().AddPlayerDat[loc]+=ammount;}
    static int GetPlayerData(int loc){return getInstance().AddPlayerDat[loc];}

    static void AddEntityType(EntityType* type);
    static int getNextTypeId();
    static int AddEntity(bool side,int type,Vector<int> meta=Vector<int>());
    static void RemoveEntity(bool side,int id);
    static void TickEntities();
    static void Draw();
    static EntityType* getType(int);
    //static std::ostream& Log();

    static void Load();
    static void Save();
    static void New();

    static void PauseUnpause();

    static void Exit();
    static void MainScreen();

    static void Setup();
};




#endif // __SYSTEM_HPP__
