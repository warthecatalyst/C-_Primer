#ifndef BLOB_H_PREFIX
#define BLOB_H_PREFIX

#include "global.h"

template <typename T> class Blob{
public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    Blob();
    Blob(std::initializer_list<T> il);
    size_type size() const {return data->size();}
    bool empty() const {return data->empty();}
    void push_back(const T& t) {data->push_back(t);}
    void push_back(const T&& t) {data->push_back(std::move(t));}
    void pop_back(){
        check(0,"back on empty Blob");
        data->pop_back();
    }
    T& back(){
        check(0,"back on empty Blob");
        return data->back();
    }
    T& operator[](size_type i){
        check(i,"out of range error");
        return (*data)[i];
    }
private:
    shared_ptr<vector<T>> data;
    void check(size_type i, const string &msg) const;
};

template <typename T>
inline Blob<T>::Blob(): data(make_shared<vector<T>>()) {}

template <typename T>
inline Blob<T>::Blob(initializer_list<T> il): data(make_shared<vector<T>>(il)) {}

template <typename T>
void Blob<T>::check(size_type i, const string &msg) const
{
    if(i>=data->size()){
        throw out_of_range(msg);
    }
}

#endif