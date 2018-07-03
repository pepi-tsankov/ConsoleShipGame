
#include"../../Headers/GUI/DrawableObject.hpp"
#include"../../Headers/GUI/Screen.hpp"

void DrawableObject::draw(char x,char y)const{
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            Screen::setCell(j+x,i+y,character[i*width+j],color[i*width+j]);
        }
    }

}
