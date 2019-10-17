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
struct ReadTuple {
    bool readTuple(std::ifstream& inFile, T& data) {
        ReadTuple<I - 1, T> reader;
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
struct ReadTuple<0, T> {
    bool readTuple(std::ifstream& inFile, T& data) {
        if (!(inFile >> std::get<0>(data))) {
            return false;
        }
        return true;
    }
};

template <size_t CUR_I, size_t I, class T>
struct Print{
    void operator()(std::ostream& out, T& data) {
        Print<CUR_I - 1, I, T> printer;
        printer(out, data);
        if (CUR_I == I) {
            out << std::get<CUR_I>(data);
        }
    }
};

template <size_t I, class T>
struct Print<0, I, T> {
    void operator()(std::ostream& out, T& data) {
        if (I == 0) {
            out << std::get<I>(data);
        }
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

    ReadTuple<sizeof ...(U) - 1, std::tuple<U...>> reader;
    while (reader.readTuple(inFile, temp)) {
        array.push_back(temp);
    }


    return array;
}

template<size_t I, class... U>
void printOne(std::tuple<U...> &tuple, std::ostream &out) {
    Print<sizeof...(U) - 1, I, std::tuple<U...>> printer;
    printer(out, tuple);
}

#endif //FIRST_READER_H
