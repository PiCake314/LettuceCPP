#include <iostream>
// #include <unordered_map>
#include "Expr.hpp"

// typedef std::unordered_map<std::string, NumVal> Environment;


template <template <typename, typename> class T, typename L, typename R>
requires std::is_base_of<Expr, T<L, R>>::value
NumVal evalExpr(T<L, R> e){

    if (std::is_same_v<T<L, R>, Num<L, R>>){
        return NumVal(e.value);
    }

    // if constexpr(std::is_same_v<T<L, R>, Var<L, R>>){
    //     if(env.find(e.name) != env.end()){
    //         return env[e.name];
    //     }
    //     throw std::runtime_error("Variable not found");
    // }

    if constexpr(std::is_same_v<T<L, R>, Plus<L, R>>){
        auto lhs = evalExpr(e.lhs);
        auto rhs = evalExpr(e.rhs);
        return NumVal(lhs.value + rhs.value);
    }
    
    if constexpr(std::is_same_v<T<L, R>, Mul<L, R>>){
        auto lhs = evalExpr(e.lhs);
        auto rhs = evalExpr(e.rhs);
        return NumVal(lhs.value * rhs.value);
    }

    if constexpr(std::is_same_v<T<L, R>, Div<L, R>>){
        auto lhs = evalExpr(e.lhs);
        auto rhs = evalExpr(e.rhs);
        return NumVal(lhs.value / rhs.value);
    }

    if constexpr(std::is_same_v<T<L, R>, Minus<L, R>>){
        auto lhs = evalExpr(e.lhs);
        auto rhs = evalExpr(e.rhs);
        return NumVal(lhs.value - rhs.value);
    }

    // if constexpr(std::is_same_v<T<L, R>, Let<L, R>>){
    //     env[e.name] = evalExpr(e.lhs, env);
    //     return evalExpr(e.rhs, env);
    // }

    // if constexpr(std::is_same_v<T<L, R>, MultiLet<L, R>>){

    // }


    throw std::runtime_error("Unknown type");
}


int main(){

    // Environment env;

    // let x = 5 in x + 2
    // auto e = Let("x", Num(5), Plus(Var("x"), Num(2)));
    auto e = Plus(Num(1), Mul(Num(2), Num(3)));

    std::cout << evalExpr(e) << std::endl;


    return 0;
}