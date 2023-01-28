#ifndef TEMPLATE_H_PREFIX
#define TEMPLATE_H_PREFIX

#include "global.h"

template<typename T>
int compare(const T &v1,const T& v2);

template <typename T> T foo(T* p);

template<typename Iterator, typename Value>
Iterator find_i(Iterator first,Iterator last,Value value);

template<typename Arr>
void print_arr(Arr const& arr);

template<typename T, unsigned size>
constexpr unsigned getSize(const T(&)[size]);
#endif