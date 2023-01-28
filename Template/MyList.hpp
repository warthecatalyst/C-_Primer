#ifndef MYLIST_HPP_PREFIX
#define MYLIST_HPP_PREFIX

#include "global.h"

namespace myownutils{

template<typename T>
struct _list_node{
    typedef _list_node* list_node_pointer;
    list_node_pointer prev;
    list_node_pointer next;
    T data;
};

template<typename T>
struct _list_iterator{
    typedef _list_iterator<T> self;
    typedef _list_node<T>* link_type;

    link_type ptr;
    _list_iterator(link_type p = nullptr):ptr(p){}

    T& operator*(){return ptr->data;}

    T* operator->(){return &(operator());}

    self& operator++(){
        ptr = ptr->next;
        return *this;
    }

    self& operator--(){
        ptr = ptr->prev;
        return *this;
    }

    bool operator==(const _list_iterator& rhs){
        return ptr == rhs.ptr;
    }

    bool operator!=(const _list_iterator& rhs){
        return !(*this==rhs);
    }
};

template<typename T>
class MyList final{
private:
    typedef _list_node<T> list_node;
    std::allocator<list_node> nodeAllocator;

public:
    typedef T value_type;
    typedef T& reference;
    typedef value_type* pointer;
    typedef list_node* link_type;
    typedef const value_type* const_pointer;

    typedef size_t size_type;

    typedef _list_iterator<value_type> iterator;

    MyList(){empty_initialize();}
    MyList(size_t n){fill_initialize(n,T());}

    iterator begin(){
        return new iterator(node->next);
    }

    iterator cbegin() const{
        return new iterator(node->next);
    }

    iterator end(){
        return new iterator(node);
    }

    iterator cend() const {
        return new iterator(node);
    }

    iterator insert(iterator position,const T& value){
        link_type tmp = alloc_ctor_node(value);
        tmp->next = position.ptr;
        tmp->prev = position.ptr->prev;

        position.ptr->prev->next = tmp;
        position.ptr->prev = tmp;

        return tmp;
    }

    void push_back(const T& value){
        insert(end(),value);
    }    

    bool empty() const {
        return node == node->next;
    }

    iterator insert(iterator position, size_t n, const T& value){
        while(n--){
            insert(position,value);
        }
    }

private:
    link_type node;

    link_type alloc_node(){
        return new _list_node();
    }

    void dealloc_node(link_type p){
        delete p;
    }

    link_type alloc_ctor_node(const T& val){
        link_type p = alloc_node();
        p->data = val;
        return p;
    }

    void dealloc_dtor_node(link_type p){
        dealloc_node(p);
    }

    void empty_initialize(){
        node = alloc_node();
        node->prev = node;
        node->next = node;
    }

    void fill_initialize(size_t n,const T& value){
        empty_initialize();
        insert(begin(),n,value);
    }
};



}


#endif