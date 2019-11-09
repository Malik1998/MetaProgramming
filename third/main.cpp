#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "ScatterHierarchy.h"

template <class T>
class Representer {
    virtual T show() {
        return val;
    }

public:
    T val;
};

template<> class Representer<int> {
    virtual int show() {
        return val;
    }

public:
    int val = -1;
};

template<> class Representer<std::string> {
    std::string show() {
        return val;
    }

public:
    std::string val = "empty";
};

int main() {
    typedef ScatterHierarchy<Tuple<int, Tuple<std::string, NullType>>, Representer>  my_composite_class;
    my_composite_class hierarchy;
    GetValue<int, Representer> int_getter;
    std::cout << (int_getter(hierarchy)) << std::endl;
    GetValue<std::string, Representer> string_getter;
    std::cout << string_getter(hierarchy) << std::endl;

    std::cout << "----------------------------------" << std::endl;
    int_getter(hierarchy) = 7;
    std::cout << (int_getter(hierarchy)) << std::endl;

    string_getter(hierarchy) = "NEWEST VALUE EVER";
    std::cout << string_getter(hierarchy) << std::endl;

    std::cout << "----------------------------------" << std::endl;
    std::cout << "By INDEX" << std::endl;
    GetValueIndex<Representer, 0> int_getter_0;
    int_getter_0(hierarchy) = 8;
    std::cout << (int_getter_0(hierarchy)) << std::endl;

    GetValueIndex<Representer, 1> string_getter_1;
    string_getter_1(hierarchy) = "NEWEST VALUE EVER By INDEX";
    std::cout << string_getter_1(hierarchy) << std::endl;


    //std:: cout << GetValue<std::string, Representer>(hierarchy) << std::endl;

//    hierarchy::inner.value = 5;

}