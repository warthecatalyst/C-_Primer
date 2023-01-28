#ifndef MYVEC_HPP_PREFIX
#define MYVEC_HPP_PREFIX
#include "global.h"

namespace myownutils{   //start namespace MyOwnUtils
template<typename T>
class MyVec final{
public:
    MyVec(): element(nullptr),first_free(nullptr), cap(nullptr){}
    MyVec(std::initializer_list<T> l);
    MyVec(const MyVec& v);

    MyVec& operator=(const MyVec& rhs);
    ~MyVec();

    //members
    void push_back(const T& t);
    void pop_back();
    T& operator[](size_t i){return *(element+i);}

    std::size_t size() const {return first_free-element;}
    std::size_t capacity() const {return cap-element;}

    T* begin() const {return element;}
    T* end() const {return first_free;}

    void reserve(size_t);
    void resize(size_t);
    void resize(size_t n,const T& t);
    void clear();

private:
    //data members
    T* element;
    T* first_free;
    T* cap;
    
    //allocator
    std::allocator<T> alloc;

    //utilities
    void reallocate();
    void check_and_alloc() {if(size()==capacity()) reallocate();}
    void free();
    
    void alloc_and_move(size_t);
    pair<T*,T*> alloc_and_copy(T* b,T* e);
};

template<typename T>
MyVec<T>::MyVec(std::initializer_list<T> list){
    T* const newData = alloc.allocate(list.size());
    T* p = newData;
    for(const auto &t:list){
        alloc.construct(p++,t);
    }

    element = newData;
    first_free = cap = element+list.size();
}

template<typename T>
MyVec<T>::MyVec(const MyVec& vect){
    pair<T*,T*> newData = alloc_and_copy(vect.begin(),vect.end());
    element = newData.first;
    first_free = cap = newData.second;
}

template<typename T>
MyVec<T>& MyVec<T>::operator=(const MyVec& rhs){
    pair<T*,T*> newData = alloc_and_copy(rhs.begin(),rhs.end());
    //destroy and deallocate
    free();
    //update data structure
    element = newData.first;
    first_free  = cap = newData.second;
    return *this;
}

template<typename T>
MyVec<T>::~MyVec(){
    free();
}

template<typename T>
void MyVec<T>::push_back(const T& t){
    check_and_alloc();
    alloc.construct(first_free++,t);
}

template<typename T>
void MyVec<T>::pop_back(){
    alloc.destroy(--first_free);
}

template<typename T>
void MyVec<T>::reserve(size_t n){
    if(n <= capacity()) return;
    alloc_and_move(n);
}

template<typename T>
void MyVec<T>::resize(size_t n){
    resize(n,T());
}

template<typename T>
void MyVec<T>::resize(size_t n,const T& t){
    if(n<size()){
        for(auto p = element+n;p!=first_free;){
            alloc.destroy(p++);
        }
        first_free = element+n;
    }
    else if(n>size()){
        for(auto i = size();i!=n;i++)
            push_back(t);
    }
    
}

//only destroy rather than deallocate
template<typename T>
void MyVec<T>::clear(){
    for(auto p = first_free;p!=element;){
        alloc.destroy(--p);
    }
    first_free = element;
}

template<typename T>
pair<T*,T*> MyVec<T>::alloc_and_copy(T* begin,T* end){
    T* data = alloc.allocate(end-begin);
    return {data, std::uninitialized_copy(begin,end,data)};
}

template<typename T>
void MyVec<T>::free(){
    if(element){
        for(auto p = first_free;p!=element;){
            alloc.destroy(--p);
        }
        alloc.deallocate(element,capacity());
    }
}

template<typename T>
void MyVec<T>::alloc_and_move(size_t n){
    size_t newCapacity = n;
    T* newData = alloc.allocate(newCapacity);

    T* dest = newData;
    T* old = element;
    for(size_t i = 0;i < size();i++){
        alloc.construct(dest++,std::move(*old++));
    }
    free();
    element = newData;
    first_free = dest;
    cap = element + newCapacity;
}

template<typename T>
void MyVec<T>::reallocate()
{
    size_t newCapacity = size()? 2*size():1;
    alloc_and_move(newCapacity);
}

}   //end namespace myownutils

#endif