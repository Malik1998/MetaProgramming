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


#endif //THIRD_SCATTERHIERARCHY_H
