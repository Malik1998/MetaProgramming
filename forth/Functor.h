//
// Created by malik on 23.11.2019.
//

#ifndef FORTH_FUNCTOR_H
#define FORTH_FUNCTOR_H

template <class ...T>
class ArgsPack;

template <>
class ArgsPack<> {
public:
    ArgsPack() = default;

    template <class Function, class...Args>
    auto Call(Function function, Args... args) -> decltype(function(args...)) {
        return function(args...);
    }
};

template <class Function>
class SimpleWrapper {
private:
    Function function_;

public:
    explicit SimpleWrapper(const Function function) : function_(function) {

    }

    template <class... Args>
    auto operator()(Args... args) -> decltype(function_(args...)) {
        return function_(args...);
    }
};

template <class Class, class Callable>
class ClassMethodWrapper {
private:
    Class& object_;
    Callable callable_;
public:
    ClassMethodWrapper(Class& object, const Callable& callable) : object_(object), callable_(callable) {
    }


    template <class... Args>
    auto operator()(Args... args) -> decltype((object_.*callable_)(args...)) {
        return (object_.*callable_)(args...);
    }
};

template<class Head, class... Tail>
class ArgsPack<Head, Tail...> : ArgsPack<Tail...> {
private:
    Head param_;

public:
    typedef ArgsPack<Tail...> base;

    explicit ArgsPack(Head param, Tail... params) :base(params...), param_(param) {

    }

    Head* ConvertToPointer(Head& param) {
        return &param_;
    }

    Head& ConvertToRef(Head& param) {
        return param_;
    }

    Head* ConvertToPointer(Head* param) {
        return param_;
    }

    Head& ConvertToRef(Head* param) {
        return *param_;
    }

    template <class Function, class...Args>
    auto Call(const Function& function, Args... args) ->
    decltype(this->base::Call(function, args..., ConvertToPointer(this->param_))) {
        return base::Call(function, args..., ConvertToPointer(param_));
    }

    template <class Function, class...Args>
    auto Call(const Function& function, Args... args) ->
    decltype(this->base::Call(function, args..., ConvertToRef(this->param_))) {
        return base::Call(function, args..., ConvertToRef(param_));
    }
};

template <class Function, class... Args>
class Functor : ArgsPack<Args...> {
private:
    Function function_;

public:

    typedef ArgsPack<Args...> base;

    Functor(Function function, Args...args) : base(args...), function_(function) {

    }

    template <class Object>
    auto Call(Object& object) ->
    decltype(base::Call(ClassMethodWrapper<Object, Function>(object, function_))) {

        return base::Call(ClassMethodWrapper<Object, Function>(object, function_));
    }

    template <class Callable = Function>
    auto Call() ->
    decltype(base::Call(SimpleWrapper<Callable>(function_))) {
        return base::Call(SimpleWrapper<Callable>(function_));
    }
};

template <class Function, class... Args>
Functor<Function, Args...> BuildFunctor(Function function, Args...args) {
    return Functor<Function, Args...>(function, args...);
}


#endif //FORTH_FUNCTOR_H
