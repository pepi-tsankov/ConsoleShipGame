#ifndef __HITBOX_HPP__
#define __HITBOX_HPP__
#include"../Vector.hpp"

class Hitbox{
Vector<char> hitbox;
char width;
char height;
char x;
char y;
public:
    Hitbox(char width,char height);
    bool operator^(const Hitbox& rhs)const;
    Hitbox copy(char x, char y)const;
    void move(int x,int y){this->x+=x;this->y+=y;}
    void set(int x,int y,bool hit){hitbox[x+(y*width)]=hit;}
    char getX(){return x;}
    char getY(){return y;}
};



#endif // __HITBOX_HPP__
