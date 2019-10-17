//
// Created by malik on 17.10.2019.
//

#ifndef SECOND_GETINDEXOF_H
#define SECOND_GETINDEXOF_H

struct NullType {

};

template<class T, class U>
struct Tuple {
    typedef T head;
    typedef U tail;
};


template <class T, class U, class S>
struct GetIndexOfPrivate {
    int operator()() {
        return (GetIndexOfPrivate <typename U::head, typename U::tail, S > ()() < 0) ?
               -1 :
               GetIndexOfPrivate <typename U::head, typename U::tail, S >()() + 1;
    }
};

template <class T, class S>
struct GetIndexOfPrivate<T, NullType, S> {
    int operator()() {
        return -1;
    }
};

template <class T, class S>
struct GetIndexOfPrivate<S, T, S> {
    int operator()() {
        return 0;
    }
};


template <class S>
struct GetIndexOfPrivate<S, NullType, S> {
    int operator()() {
        return 0;
    }
};

template <class T, class S>
struct GetIndexOf {
    int operator()() {
        return GetIndexOfPrivate <typename T::head, typename T::tail, S > ()();
    }
};

#endif //SECOND_GETINDEXOF_H
