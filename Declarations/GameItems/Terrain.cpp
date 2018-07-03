#include"../../Headers/GameItems/Terrain.hpp"
#include"../../Headers/GUI/Screen.hpp"
#include<stdlib.h>

int Terrain::startingMetaLocation(){
    return 0;
}
int Terrain::storedMeta(){
    return 1;
}
void Terrain::tickEntity(Entity* entity)const{
    setMeta(entity,0,(getMeta(entity,0)+1)%24000);
}
float noise(int,float,int,int);
void Terrain::drawEntity(Entity* entity)const{
    int mask1=0b00101111;
    int mask2=~0b01010000;
    int time=getMeta(entity,0);
    for(int x=0;x<100;++x){
        int height=noise(time+x,7,2373,200)+noise(time+x+5,3,5789,30);
        for(int y=2;y<28;++y){
            if((28-y)<height){
                mask1=0b00101111;
                mask2=~0b01010000;
            }else{
                mask2=~0;
                mask1=0;
            }
            int c=(time+x+4*y)%24000;
            if(c<5000||c>=23000){//Night
                Screen::setCell(x,y,' ',(0b00001111|mask1)&mask2);
            }else if(c<7000){//Transition night-day phase 1
                srand(c+(y<<5^0b1001101));
                if(((rand()%2000)+5000)>c){
                    Screen::setCell(x,y,' ',(0b00001111|mask1)&mask2);
                }else{
                    Screen::setCell(x,y,' ',(0b00011111|mask1)&mask2);
                }
            }else if(c>=21000){//Transition day-night phase 2
                srand(c+(y<<5^0b1001101));
                if(((rand()%2000)+22000)>c){
                    Screen::setCell(x,y,' ',(0b00011111|mask1)&mask2);
                }else{
                    Screen::setCell(x,y,' ',(0b00001111|mask1)&mask2);
                }
            }else if(c<9000){//Transition night-day phase 2
                srand(c+(y<<5^0b1001101));
                if(((rand()%2000)+7000)>c){
                    Screen::setCell(x,y,' ',(0b00011111|mask1)&mask2);
                }else{
                    Screen::setCell(x,y,' ',(0b10011111|mask1)&mask2);
                }
            }else if(c>=19000){//Transition day-night phase 1
                srand(c+(y<<5^0b1001101));
                if(((rand()%2000)+19000)>c){
                    Screen::setCell(x,y,' ',(0b10011111|mask1)&mask2);
                }else{
                    Screen::setCell(x,y,' ',(0b00011111|mask1)&mask2);
                }
            }else{//Day
                Screen::setCell(x,y,' ',(0b10011111|mask1)&mask2);
            }
        }
    }
}

Entity Terrain::createEntity(int id,Vector<int> metadata)const{
    Entity rs=EntityType::createEntity(id,metadata);
    if(metadata.getSize()==0){
        addMeta(&rs,5000);
    }else{
        addMeta(&rs,metadata[0]);
    }
    return rs;
}

float noise(int x,float height, int seed,int width){
    if(x%width==0) return height*0.5f;
    int x_lt=x/width;
    int x_rt=x_lt+1;
    srand(seed+x_lt);
    float a=height*((5-rand()%11)/(2.5f*width));
    srand(seed+x_rt);
    float b=height*((5-rand()%11)/(2.5f*width));
    //return a*((1-(x%width))/width)+b*((x%width)/width)+height/2;
    return ((a*(x%width)*(width-(x%width)))/width+(b*((x%width)-width)*(x%width))/width+height)*0.5f;
}
