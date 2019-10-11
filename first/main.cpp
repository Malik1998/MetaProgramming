#include <iostream>
#include <fstream>
#include <ostream>
#include "FirstType/Reader.h"

void TestFirstProgramm_1(const std::string& filename) {
    std::ifstream inFile;

    inFile.open(filename);

    Reader<int, int, float> reader;

    auto array = reader.Read(inFile);

    for (auto& elem: array) {
        std::cout << "STANDARD FUNCTION: " << std::endl;
        std::cout << std::get<0>(elem) << " " << std::get<1>(elem) << " " << std::get<2>(elem) << std::endl;
        std::cout << "TEMPLATE FUNCTION: " << std::endl;
        printOne<0, int, int, float>(elem, std::cout);
        std::cout << " ";
        printOne<1, int, int, float>(elem, std::cout);
        std::cout << " ";
        printOne<2, int, int, float>(elem, std::cout);
        std::cout << std::endl;
        std::cout << "------------------" << std::endl;
    }
}

void TestFirstProgramm_2(const std::string& filename) {
    std::ifstream inFile;

    inFile.open(filename);

    Reader<int, std::string, float> reader;

    auto array = reader.Read(inFile);

    for (auto& elem: array) {
        std::cout << "STANDARD FUNCTION: " << std::endl;
        std::cout << std::get<0>(elem) << " " << std::get<1>(elem) << " " << std::get<2>(elem) << std::endl;
        std::cout << "TEMPLATE FUNCTION: " << std::endl;
        printOne<0, int, std::string, float>(elem, std::cout);
        std::cout << " ";
        printOne<1, int, std::string, float>(elem, std::cout);
        std::cout << " ";
        printOne<2, int, std::string, float>(elem, std::cout);
        std::cout << std::endl;
        std::cout << "------------------" << std::endl;
    }
}



int main() {
    std::cout << "Hello, World!" << std::endl;
    TestFirstProgramm_1("../FirstExample.txt");
    std::cout << "------------------" << std::endl;
    std::cout << "------------------" << std::endl;
    TestFirstProgramm_2("../SecondExample.txt");
    return 0;
}