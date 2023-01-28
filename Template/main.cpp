#include "template.h"
#include "Blob.hpp"
#include "MyVec.hpp"
#include "MyList.hpp"

template<typename T>
int compare(const T &v1,const T& v2){
    if (v1 < v2) return -1;
    if (v1 > v2) return 1;
    return 0;
}

template <typename T> T foo(T* p){
    T tmp = *p;
    return tmp;
}

template<typename Iterator, typename Value>
Iterator find_i(Iterator first,Iterator last,Value value){
    for(;first != last && *first != value;first++);
    return first;
}

template<typename Arr>
void print_arr(Arr const& arr){
    for (const auto& elem:arr){
        cout << elem << " ";
    }    
    cout << endl;
}

template<typename T, unsigned size>
constexpr unsigned getSize(const T(&)[size])
{
    return size;
}

void test_my_vector(){
    cout << "\n\nin test my vector" << endl;
    myownutils::MyVec<int> my_vector;
    my_vector.push_back(1);
    my_vector.push_back(2);
    my_vector.push_back(3);
    my_vector.push_back(4);
    for(int i = 0;i<my_vector.size();i++){
        cout << my_vector[i] << ", ";
    }
    cout << endl;
    my_vector.resize(10,3);
    for(int i = 0;i<my_vector.size();i++){
        cout << my_vector[i] << ", ";
    }
    cout << endl;
    my_vector.clear();
    for(int i = 0;i<my_vector.size();i++){
        cout << my_vector[i] << ", ";
    }
    cout << endl;
}

void test_my_list(){
    cout <<"In test MyList" << endl;
    myownutils::MyList<int> my_list(5);
}

int main(int argc,char **argv){
    string s1 = "123";
    string s2 = "456";
    int x1 = 123;
    int x2 = 456;
    cout << compare(s1,s2) << endl;
    cout << compare(x2,x1) << endl;
    cout << foo(&s2) << endl;
    vector<string> vec = {"123","456","789"};
    auto iter = find_i(vec.begin(),vec.end(),"456");
    cout << *iter << endl;
    string strs[] = {"test0","test1","test2"};
    char characters[] = {'a','b','c'};
    int numbers[] = {1,2,3,4,5};
    print_arr(strs);
    print_arr(characters);
    print_arr(numbers);
    cout << getSize(strs) << ", " << getSize(characters) << ", " << getSize(numbers) << endl;
    Blob<int> blobs;
    blobs.push_back(1);
    blobs.push_back(2); 
    test_my_vector();    
}