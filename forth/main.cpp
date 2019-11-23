#include <iostream>
#include "Functor.h"
#include <string>

void TrySimpleFunction() {
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "TRY SIMPLE FUNCTION" << std::endl;

    auto function = [](int a, int* b, float c, const std::string& d) {
        std::cout << a << " " << *b << " " << c << " " << d << std::endl;
    };

    auto functor = BuildFunctor(function, 1, 5, 0.3, "hello");

    functor.Call();
    std::cout << "End TRYing SIMPLE FUNCTION" << std::endl;
    std::cout << "_______________________________________" << std::endl;
    std::cout << std::endl;
}

class MyClass {
public:
    MyClass(int id) : id_(id) {

}
    void Print(int a, const std::string& b) {
        std::cout << "class function " << a << " " << b  << " my id is " << id_ << std::endl;
    }

private:
    int id_ = -1;
};

void TryClassMemeberFunction() {
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "TRY ClASS FUNCTION" << std::endl;


    MyClass myClass {5};
    auto functor = BuildFunctor(&MyClass::Print, 5, "hello");
    functor.Call(myClass);
    std::cout << "End TRYing Class FUNCTION" << std::endl;
    std::cout << "_______________________________________" << std::endl;
}

int main() {
    TrySimpleFunction();
    TryClassMemeberFunction();

}