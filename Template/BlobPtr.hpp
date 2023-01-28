#ifndef BLOB_PTR_H_PREFIX
#define BLOB_PTR_H_PREFIX

#include "Blob.hpp"
#include "global.h"
template<typename T> class BlobPtr{
public:
    BlobPtr(): curr(0) {}
    BlobPtr(Blob<T> &a, size_t sz = 0):wptr(a.data),curr(sz){}
    T& operator*() const{
        auto p = check(curr,"dereference pass end");
        return (*p)[curr];
    }

    BlobPtr& operator++();
    BlobPtr& operator--();

private:
    shared_ptr<vector<T>> check(size_t, const string&) const;
    weak_ptr<vector<T>> wptr;
    size_t curr;
};

template<typename T>
BlobPtr<T>& BlobPtr<T>::operator++(){
    ++curr;
    return *this;
}

template<typename T>
BlobPtr<T>& BlobPtr<T>::operator--(){
    --curr;
    return *this;
}

template <typename T>
inline shared_ptr<vector<T>> BlobPtr<T>::check(size_t sz, const string &msg) const
{
    if(sz<0||sz>wptr->size()){
        throw out_of_range(msg);
    }
    return make_shared(wptr);
}

#endif