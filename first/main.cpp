#include <iostream>
#include <fstream>
#include "FirstType/Reader.h"

void TestFirstProgramm_1(const std::string& filename) {
    std::ifstream inFile;

    inFile.open(filename);

    Reader<int, int, float> reader;

    auto array = reader.Read(inFile);

    for (auto& elem: array) {
        std::cout << std::get<0>(elem) << " " << std::get<1>(elem) << " " << std::get<2>(elem) << std::endl;
    }
}

void TestFirstProgramm_2(const std::string& filename) {
    std::ifstream inFile;

    inFile.open(filename);

    Reader<int, std::string, float> reader;

    auto array = reader.Read(inFile);

    for (auto& elem: array) {
        std::cout << std::get<0>(elem) << " " << std::get<1>(elem) << " " << std::get<2>(elem) << std::endl;
    }
}



int main() {
    std::cout << "Hello, World!" << std::endl;
    TestFirstProgramm_1("../FirstExample.txt");
    std::cout << "------------------" << std::endl;
    TestFirstProgramm_2("../SecondExample.txt");
    return 0;
}