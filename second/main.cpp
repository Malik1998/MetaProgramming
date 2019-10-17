#include <iostream>
#include "GetIndexOf.h"
#include <string>

struct SmallType {

};

struct MyType {

    int a, b, c;
    std::string d;
    SmallType small;
};

int main() {

    std::cout << GetIndexOf< Tuple<int,Tuple<double, Tuple<float, NullType>>>, float>()() << " == " << 2 << " ? \n";
    std::cout << GetIndexOf< Tuple<int,Tuple<MyType, Tuple<float, NullType>>>, MyType>()() << " == " << 1 << " ? \n";
    std::cout << GetIndexOf< Tuple<int,Tuple<double, Tuple<float, NullType>>>, std::string>()() << " == " << -1 << " ? \n";
    std::cout << GetIndexOf< Tuple<int,Tuple<double, Tuple<SmallType, NullType>>>, SmallType>()() << " == " << 2 << " ? \n";
    std::cout << GetIndexOf< Tuple<int,Tuple<double, Tuple<float, NullType>>>, MyType>()() << " == " << -1 << " ? \n";
}