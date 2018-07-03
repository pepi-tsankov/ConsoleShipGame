#ifndef __VECTOR_H__P__
#define __VECTOR_H__P__
#include <stddef.h>
#include<iostream>
template <class type>
class Vector{
    int size_;
    int capacity_;
    type* storage;
    void resize_();
    type* manageMemory();
    void isInRange(int i)const;
    bool range(int i)const;
public:
    Vector():size_(0),capacity_(0),storage(NULL){}
    Vector(const type* const arr,unsigned size_);
    Vector(unsigned capacity):size_(0),capacity_(capacity){storage=new type[capacity];}
    int getSize() const{return size_;}
    ~Vector(){delete[] storage;}
    bool isEmpty(){return size_==0;}

    bool operator!=(const Vector<type> &obj) const;
    type& operator[](int position);
    const type& operator[](int position)const;
    Vector(const Vector<type> &obj);
    bool operator ==(const Vector<type> &obj) const;
    bool equals(const type* const obj,int length) const;
    Vector<type>& operator = (const Vector<type>& obj);
    Vector<type>& cropToSize();
    Vector<type>& pushBack(type obj);
    Vector<type>& removeElementAt(int pos);
    Vector<type>& removeElementAt(int pos,const std::nothrow_t& tag);
    template <class T>
    friend std::ostream& operator<<(std::ostream& os,const Vector<T> &a);
};
#include"../Declarations/Vector.inl"
#endif // __VECTOR_H__P__
