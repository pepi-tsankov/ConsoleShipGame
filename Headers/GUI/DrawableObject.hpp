#ifndef __DRAWABLEOBJECT_HPP_P__
#define __DRAWABLEOBJECT_HPP_P__
#include"../Vector.hpp"

class DrawableObject{
    Vector<char> color;
    Vector<char> character;
    int width;
    int height;
public:
    DrawableObject(int width, int height):width(width),height(height){for(int i=0;i<width*height;i++){color.pushBack(0x0F);character.pushBack(' ');}}
    void setAt(int x,int y, char col, char chr){color[x+y*width]=col;character[x+y*width]=chr;}
    int getWidth()const{return width;}
    int getHeight()const{return height;}
    char getColorAt(int x,int y)const{return color[x+y*width];}
    char getCharAt(int x,int y)const{return character[x+y*width];}
    void draw(char x,char y)const;
};
#endif // __DRAWABLEOBJECT_HPP_P__
