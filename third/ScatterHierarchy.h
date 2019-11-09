//
// Created by malik on 09.11.2019.
//

#ifndef THIRD_SCATTERHIERARCHY_H
#define THIRD_SCATTERHIERARCHY_H

struct NullType {

};

template<class T, class U>
struct Tuple {
    typedef T head;
    typedef U tail;
};

template <class T, class U, int I>
struct GetTypeAt {
    typedef typename GetTypeAt<typename U::head, typename U::tail, I - 1>::result result;
};

template <class T, class U>
struct GetTypeAt<T, U, 0> {
    typedef T result;
};

template <class List, template <class> class Class>
class ScatterHierarchy;

template <class U, class T, template <class> class Class>
class ScatterHierarchy<Tuple<U, T>, Class> : public ScatterHierarchy<U, Class>, public ScatterHierarchy<T, Class> {

public:
    typedef Tuple<U, T> list_types;
    typedef ScatterHierarchy<U, Class> inner;
    typedef ScatterHierarchy<T, Class> next;
};

template <class Type, template <class> class Class>
class ScatterHierarchy : public Class<Type> {
public:
    typedef Class<Type> base;
};

template <template <class> class Class>
class ScatterHierarchy<NullType, Class> {
};

template <class ReturnValue, class List, class CurType, template <class> class Class>
struct GetValueSecond {
    ReturnValue& operator()(List& element) {
        return GetValueSecond<ReturnValue, typename List::next, typename List::inner, Class>()(element);
    }
};

template <class ReturnValue, class List, template <class> class Class>
struct GetValueSecond <ReturnValue, List, ScatterHierarchy<ReturnValue, Class>, Class> {
    ReturnValue& operator()(Class<ReturnValue>& element) {
        return element.val;
    }
};

template <class ReturnValue, template <class> class Class>
struct GetValue {
    template <class List>
    ReturnValue& operator()(List& list) {
        return GetValueSecond<ReturnValue, typename List::next, typename List::inner, Class>()(list);
    }
};

template <class ReturnValue, class List, class CurType, template <class> class Class, int Index>
struct GetValueSecondIndex {
    ReturnValue& operator()(List& element) {
        return GetValueSecondIndex<ReturnValue, typename List::next, typename List::inner, Class, Index - 1>()(element);
    }
};

template <class ReturnValue, class List, template <class> class Class>
struct GetValueSecondIndex <ReturnValue, List, ScatterHierarchy<ReturnValue, Class>, Class, 0> {
    ReturnValue& operator()(Class<ReturnValue>& element) {
        return element.val;
    }
};



template <template <class> class Class, int Index>
struct GetValueIndex {
    template <class List>
    typename GetTypeAt<typename List::list_types::head, typename List::list_types::tail, Index>::result & operator()(List& list) {
        return GetValueSecondIndex<typename GetTypeAt<typename List::list_types::head, typename List::list_types::tail, Index>::result, typename List::next, typename List::inner, Class, Index>()(list);
    }
};


#endif //THIRD_SCATTERHIERARCHY_H
