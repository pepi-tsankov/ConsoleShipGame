#include"../Headers/Vector.hpp"
#include<ostream>
#include<stdexcept>
template<class T>

inline Vector<T>::Vector(const Vector<T> &obj):size_(obj.size_),capacity_(obj.size_){
    this->storage=new T[capacity_];
    for(unsigned i=0;i<size_;i++){
        this->storage[i]=obj.storage[i];
    }
}

template<class T>
inline Vector<T>::Vector(const T* const arr,unsigned size_):size_(size_),capacity_(size_){
    this->storage=new T[capacity_];
    for(unsigned i=0;i<size_;i++){
        this->storage[i]=arr[i];
    }
}

template<class T>
inline bool Vector<T>::operator ==(const Vector<T> &obj) const{
    if(this->size_!=obj.size_) return false;
    for(unsigned i=0;i<size_;i++){
        if(this->storage[i]!=obj.storage[i]) return false;
    }
    return true;
}

template<class T>
inline bool Vector<T>::equals(const T* const other,int length) const{
    if(this->size_!=length) return false;
    for(unsigned i=0;i<size_;i++){
        if(this->storage[i]!=other[i]) return false;
    }
    return true;
}

template<class T>
inline bool Vector<T>::operator !=(const Vector<T>& obj) const{
    return !((*this)==obj);
}

template<class T>
inline Vector<T>& Vector<T>::operator = (const Vector<T>& obj){
    if((*this)==obj) return (*this);
    delete[] this->storage;
    this->capacity_=obj.size_;
    this->size_=obj.size_;
    this->storage=new T[capacity_];
    for(unsigned i=0;i<size_;i++){
        this->storage[i]=obj.storage[i];
    }
    return (*this);
}

template<class T>
inline Vector<T>& Vector<T>::cropToSize(){
    T* storage_new=new T[size_];
    for(unsigned i=0;i<size_;i++){
        storage_new[i]=storage[i];
    }
    delete[] storage;
    storage=storage_new;
    capacity_=size_;
    return (*this);
}

template<class T>
inline Vector<T>& Vector<T>::pushBack(T obj){
    if(size_>=capacity_){
        resize_();
    }
    storage[size_]=obj;
    size_++;
    return (*this);
}

template<class T>
inline void Vector<T>::resize_(){
    T* storage_new=manageMemory();
    if(storage_new==storage) return;
    for(unsigned i=0;i<size_;i++){
        storage_new[i]=storage[i];
    }
    delete[] storage;
    storage=storage_new;
}

template<class T>
inline Vector<T>& Vector<T>::removeElementAt(int pos){
    isInRange(pos);
    for(int i=pos+1;i<size_;i++){
        (*this)[i-1]=(*this)[i];
    }
    size_--;
    return (*this);
}

template<class T>
inline Vector<T>& Vector<T>::removeElementAt(int pos,const std::nothrow_t& tag){
    if(range(pos)){
        for(int i=pos+1;i<size_;i++){
            (*this)[i-1]=(*this)[i];
        }
        size_--;
    }
    return (*this);
}

template<class T>
inline T* Vector<T>::manageMemory(){
    T* mem=0;
    unsigned new_s=capacity_*2;
    if(new_s==0) new_s=4;
    while(size_==capacity_){
        if(new_s<=capacity_) return storage;
        try{
            mem=new T[new_s];
            capacity_=new_s;
        }
        catch(std::bad_alloc&){
            mem=0;
            new_s= (int)((double)new_s*0.9d);
        }
    }
    if(mem==0) mem=storage;
    return mem;
}

template<class T>
inline std::ostream& operator<<(std::ostream& os,const Vector<T> &V){
    os<<V.size_<<std::endl;
    for(int i=0;i<V.size_;i++){
        os<<V.storage[i];
        os<<std::endl;
    }
    return os;
}

template<class T>
inline std::istream& operator>>(std::istream& is,Vector<T> &V){
    int elements;
    V=Vector<T>();
    is>>elements;
    for(int i=0;i<elements;i++){
        T element;
        is>>element;
        V.pushBack(element);
    }
    return is;
}


template<class T>
inline T& Vector<T>::operator[](int position){
    isInRange(position);
    return storage[position];
}

template<class T>
inline const T& Vector<T>::operator[](int position)const{
    this->isInRange(position);
    return storage[position];
}

template<class T>
inline void Vector<T>::isInRange(int i)const{
    if(!range(i)){
        throw std::out_of_range("Outside of Vector bounds");
    }
}

template<class T>
inline bool Vector<T>::range(int i)const{
    if(i<0||i>=size_){
        return false;
    }
    return true;
}
