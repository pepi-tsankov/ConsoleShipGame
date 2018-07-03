#include"../../Headers/GameItems/System.hpp"
#include"../../Headers/GameItems/Entity.hpp"
#include"../../Headers/GameItems/BasicEntityTypes.hpp"
#include"../../Headers/GameItems/hitbox.hpp"
#include"../../Headers/GameItems/Terrain.hpp"
#include"../../Headers/GameItems/Friendlies/Player.hpp"
#include"../../Headers/GameItems/Friendlies/PlayerRocket.hpp"
#include"../../Headers/GameItems/Friendlies/PlayerBullet.hpp"
#include"../../Headers/GameItems/Friendlies/PlayerExplosion.hpp"
#include"../../Headers/GameItems/Enemies/StartButton.hpp"
#include"../../Headers/GameItems/Enemies/ExitButton.hpp"
#include"../../Headers/GameWrapper.hpp"
#include"../../Headers/GameItems/Enemies/Help.hpp"
#include"../../Headers/GameItems/Enemies/LoadButton.hpp"
#include"../../Headers/GameItems/Enemies/TitleScreenButton.hpp"
#include"../../Headers/GameItems/Enemies/SaveButton.hpp"
#include"../../Headers/GameItems/Enemies/DeathMsg.hpp"

#include"../../Headers/GameItems/Enemies/EnemyPlane01.hpp"
#include"../../Headers/GameItems/Enemies/EnemyPlane02.hpp"

#include"../../Headers/GameItems/Enemies/LevelSpawner01.hpp"
#include"../../Headers/GameItems/Enemies/LevelSpawner02.hpp"

#include"../../Headers/GameItems/Enemies/EnemyBullet01.hpp"

#include"../../Headers/GameItems/Enemies/EnemyBoss01.hpp"

#include"../../Headers/GUI/Screen.hpp"
#include"../../Headers/GameItems/Enemies/Shop.hpp"
#include"../../Headers/GameItems/Enemies/DmgBuy.hpp"
#include"../../Headers/GameItems/Enemies/CDbuy.hpp"
#include"../../Headers/GameItems/Enemies/HealthBuy.hpp"
#include"../../Headers/GameItems/Enemies/HealthReduced.hpp"
#include"../../Headers/GameItems/Friendlies/Helper.hpp"

#include<fstream>

/*std::ostream& System::Log(){
    static std::ofstream os("log.txt");
    return os;
}*/
int System::AddEntity(bool side,int type,Vector<int> meta){
    System& sys=getInstance();
    Entity e;
    int id;
    if(side){
        id=sys.friendlies.getSize();
        e=sys.types[type]->createEntity(id,meta);
        sys.friendlies.pushBack(e);
    }else{
        id=sys.foes.getSize();
        e=sys.types[type]->createEntity(id,meta);
        sys.foes.pushBack(e);
    }
    //Log()<<"Added Entity id:"<<id<<" side:"<<side<<" type:"<<type<<std::endl;
    return id;
}

void System::AddEntityType(EntityType* type){
    getInstance().types.pushBack(type);
}

int System::getNextTypeId(){
    return getInstance().types.getSize();
}

System::~System(){
    for(int i=types.getSize()-1;i>=0;--i){
        delete types[i];types.removeElementAt(i);
    }
}

void System::RemoveEntity(bool side,int id){
    //Log()<<"Removed Entity: id:"<<id<<" side:"<<side<<std::endl;
    System& inst=getInstance();
    if(side){
        inst.friendlies.removeElementAt(id);
    }else{
        inst.foes.removeElementAt(id);
    }
    for(int i=((side)?inst.friendlies.getSize():inst.foes.getSize())-1;i>=0;--i){
        //Log()<<"Reidentified Entity: id:";
        if(side){
            //Log()<<inst.friendlies[i].getId();
            inst.friendlies[i]=inst.friendlies[i].copy(i);
        }else{
            //Log()<<inst.foes[i].getId();
            inst.foes[i]=inst.foes[i].copy(i);
        }
        //Log()<<" side:"<<side<<" new id:"<<i<<std::endl;
    }
}

System& System::getInstance(){
    static System instance;
    return instance;
}

EntityType* System::getType(int id){
    return getInstance().types[id];
}

void System::Draw(){
    System& sys=getInstance();
    sys.background.draw();
    for(int i=sys.foes.getSize()-1;i>=0;--i){
        sys.foes[i].draw();
    }
    for(int i=sys.friendlies.getSize()-1;i>=0;i--){
        sys.friendlies[i].draw();
    }
    int points=sys.AddPlayerDat[0];
    int coins=sys.AddPlayerDat[1];
    int dmg=sys.AddPlayerDat[2];
    int cooldown=sys.AddPlayerDat[3];
    char color[10]={0x0f,0x0f,0x0f,0b1110,0b1100,0b1100,0b1100,0b1001,0b1001};
    Screen::write(91,0,"pts",color,3);
    for(int i=0;points>0||i==0;++i,points/=10){
        Screen::setCell(90-i,0,'0'+points%10,0b0111);
    }
    Screen::write(61,0,"dmg",color+4,3);
    for(int i=0;dmg>0;++i,dmg/=10){
        Screen::setCell(60-i,0,'0'+dmg%10,0b0111);
    }
    Screen::write(76,0,"o",color+3,1);
    for(int i=0;coins>0||i==0;++i,coins/=10){
        Screen::setCell(75-i,0,'0'+coins%10,0b0111);
    }
    Screen::write(46,0,"AS",color+7,2);
    for(int i=0;cooldown>0;++i,cooldown/=10){
        Screen::setCell(45-i,0,'0'+cooldown%10,0b0111);
    }
}

void System::TickEntities(){
    System& sys=getInstance();
    sys.background.Tick();
    for(int i=sys.foes.getSize()-1;i>=0;--i){
        sys.foes[i].Tick();
    }
    for(int i=sys.friendlies.getSize()-1;i>=0;i--){
        sys.friendlies[i].Tick();
    }
    for(int i=sys.friendlies.getSize()-1;i>=0;i--){
        LivingEntity* typeA=((LivingEntity*)sys.friendlies[i].getType());//friendly type
        Hitbox boxA=typeA->getColisionBox(&(sys.friendlies[i]));
        for(int j=sys.foes.getSize()-1;j>=0;--j){
            LivingEntity* typeB=((LivingEntity*)sys.foes[j].getType()); //foe type
            if(boxA^typeB->getColisionBox(&(sys.foes[j]))){
                //Log()<<"hit 2 entities"<<std::endl;
                int cda=typeA->getColisionDamage(&sys.friendlies[i]);  //friendly dmg
                int cdb=typeB->getColisionDamage(&sys.foes[j]);        //foe dmg
                typeA->damage(&sys.friendlies[i],cdb);  //damage friendly by foe
                typeB->damage(&sys.foes[j],cda);        //damage foe by friendly
            }
        }
    }
    for(int i=sys.foes.getSize()-1;i>=0&&sys.continue_;--i){
        ((LivingEntity*)sys.foes[i].getType())->KillTick(&sys.foes[i]);//Log()<<"here1"<<std::endl;
    }
    for(int i=sys.friendlies.getSize()-1;i>=0&&sys.continue_;i--){
        ((LivingEntity*)sys.friendlies[i].getType())->KillTick(&sys.friendlies[i]);//Log()<<"here2"<<std::endl;
    }
    sys.continue_=true;

}

System::System(){}

void System::Setup(){
    AddEntityType(new Terrain(0));
    AddEntityType(new Player(1));
    AddEntityType(new PlayerRocket(2));
    AddEntityType(new PlayerBullet(3));
    AddEntityType(new PlayerExplosion(4));
    AddEntityType(new StartButton(5));
    AddEntityType(new ExitButton(6));
    AddEntityType(new Help(7));
    AddEntityType(new LoadButton(8));
    AddEntityType(new TitleScreenButton(9));
    AddEntityType(new SaveButton(10));
    AddEntityType(new DeathMsg(11));
    AddEntityType(new EnemyPlane01(12));
    AddEntityType(new LevelSpawner01(13));
    AddEntityType(new EnemyPlane02(14));
    AddEntityType(new EnemyBullet01(15));
    AddEntityType(new EnemyBoss01(16));
    AddEntityType(new Shop(17));
    AddEntityType(new CDbuy(18));
    AddEntityType(new DmgBuy(19));
    AddEntityType(new HealthBuy(20));
    AddEntityType(new HealthReduced(21));
    AddEntityType(new LevelSpawner02(22));
    //AddEntityType(new Helper(23));
}

void System::MainScreen(){
    System& inst=getInstance();
    inst.clean();
    inst.background=inst.types[0]->createEntity(0);
    inst.AddEntity(1,1);
    inst.AddEntity(0,5);//new game button
    inst.AddEntity(0,6);//exit button
    inst.AddEntity(0,7);//help
    inst.AddEntity(0,8);//;load button
    inst.state=1;
    inst.AddPlayerDat=Vector<int>(5);
    inst.AddPlayerDat.pushBack(0);
    inst.AddPlayerDat.pushBack(100);
    inst.AddPlayerDat.pushBack(2);
    inst.AddPlayerDat.pushBack(6);
    inst.AddPlayerDat.pushBack(0);
    inst.AddPlayerDat.pushBack(0);
}

void System::clean(){
    //Log()<<"clean system"<<std::endl;
    foes=Vector<Entity>();
    friendlies=Vector<Entity>();
    continue_=false;
}

void System::PauseUnpause(){
    System& inst=getInstance();
    if(inst.state==0){
        std::ofstream tmp_save("pause.bin"/*,std::ios::out|std::ios::binary*/);
        tmp_save<<inst.background<<std::endl;
        tmp_save<<inst.foes<<std::endl;
        tmp_save<<inst.friendlies<<std::endl;
        tmp_save<<inst.AddPlayerDat<<std::endl;
        inst.clean();
        AddEntity(1,1);
        inst.background=inst.types[0]->createEntity(0);
        inst.AddEntity(0,10);//;save button
        inst.AddEntity(0,8);//;load button
        inst.AddEntity(0,9);//;title screen button
        inst.state=2;
        inst.continue_=false;
    }else if(inst.state==2){
    //Log()<<"here"<<std::endl;
        std::ifstream tmp_save("pause.bin"/*,std::ios::in|std::ios::binary*/);
        tmp_save>>inst.background;
        tmp_save>>inst.foes;
        tmp_save>>inst.friendlies;
        tmp_save>>inst.AddPlayerDat;
        inst.state=0;
    }
}

void System::Save(){
    std::ifstream tmp_save("pause.bin",std::ios::in|std::ios::binary);
    std::ofstream save("save.bin",std::ios::out|std::ios::binary);
    char c[100];
    while(tmp_save){
        tmp_save.read(c,100);
        save.write(c,tmp_save.gcount());
    }
}

void System::Load(){
    std::ifstream save("save.bin");
    if(!save){
        System::New();
    }else{
        System& inst=getInstance();
        inst.clean();
        save>>inst.background;
        save>>inst.foes;
        save>>inst.friendlies;
        save>>inst.AddPlayerDat;
        inst.state=0;
    }
}

void System::New(){
    System& sys=getInstance();
    sys.clean();
    sys.state=0;
    AddEntity(1,1);
    sys.background=sys.types[0]->createEntity(0);
    AddEntity(0,13);//level 1 spawner class
    //AddEntity(1,23);
}

void System::Exit(){
    GameWrapper::exit();
}
