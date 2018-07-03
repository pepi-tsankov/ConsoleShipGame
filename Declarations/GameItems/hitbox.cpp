#include"../../Headers/GameItems/hitbox.hpp"

Hitbox Hitbox::copy(char x,char y)const{
    Hitbox h(*this);
    h.x=x;
    h.y=y;
    return h;
}

Hitbox::Hitbox(char width, char height):width(width),height(height){
    for(int i=0;i<width*height;i++){
        hitbox.pushBack(1);
    }
}

bool Hitbox::operator^(const Hitbox& rhs)const{
    if((width==0)||(height==0)||(rhs.x+rhs.width<=x)||(x+width<=rhs.x)||(rhs.y+rhs.height<=y)||(y+height<=rhs.y)){
        return false;
    }
    int st_x=std::min(x+width,rhs.x+rhs.width);
    int st_y=std::min(y+height,rhs.y+rhs.height);
    for(int i=std::max(y,rhs.y);i<st_y;i++){
        for(int j=std::max(x,rhs.x);j<st_x;j++){
            if(hitbox[(i-y)*width+(j-x)]&&rhs.hitbox[(i-rhs.y)*rhs.width+(j-rhs.x)]){
                return true;
            }
        }
    }
    return false;
}
