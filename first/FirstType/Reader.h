//
// Created by malik on 10.10.2019.
//

#ifndef FIRST_READER_H
#define FIRST_READER_H

#include <string>
#include <vector>
#include <tuple>
#include <type_traits>

template <size_t I, class T>
struct reader{
    bool readTuple(std::ifstream& inFile, T& data) {
        reader<I - 1, T> reader;
        if (!reader.readTuple(inFile, data)) {
            return false;
        }
        if (inFile >> std::get<I>(data)) {
            return true;
        } else {
            return false;
        }
    }
};

template <class T>
struct reader<0, T> {
    bool readTuple(std::ifstream& inFile, T& data) {
        if (!(inFile >> std::get<0>(data))) {
            return false;
        }
        return true;
    }
};

template <class ...U>
class Reader {
public:
    std::vector<std::tuple<U...>> Read(std::ifstream& inFile);

};

template<class... U>
std::vector<std::tuple<U...>>  Reader<U...>::Read(std::ifstream &inFile) {
    std::vector<std::tuple<U...>> array;

    std::tuple<U...> temp;

    reader<sizeof ...(U) - 1, std::tuple<U...>> reader;
    while (reader.readTuple(inFile, temp)) {
        array.push_back(temp);
    }


    return array;
}

#endif //FIRST_READER_H
