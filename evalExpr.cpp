#include <iostream>
#include <unordered_map>
#include "Expr.hpp"

typedef std::unordered_map<std::string, NumVal> Environment;


template <template <typename, typename> class T, typename L, typename R>
requires std::is_base_of<Expr, T<L, R>>::value
NumVal evalExpr(const T<L, R>& e, Environment env){

    auto lambdaEval = [&env](auto& expr){
        return evalExpr(expr, env);
    };

    if (std::is_same_v<T<L, R>, Num<L, R>>){
        return NumVal(e.value);
    }

    if constexpr(std::is_same_v<T<L, R>, Var<L, R>>){
        if(env.find(e.name) != env.end()){
            return env.at(e.name);
        }
        throw std::runtime_error("Variable not found");
    }

    if constexpr(std::is_same_v<T<L, R>, Plus<L, R>>){
        auto lhs = evalExpr(e.lhs, env);
        auto rhs = evalExpr(e.rhs, env);
        return NumVal(lhs.value + rhs.value);
    }
    
    if constexpr(std::is_same_v<T<L, R>, Mul<L, R>>){
        auto lhs = evalExpr(e.lhs, env);
        auto rhs = evalExpr(e.rhs, env);
        return NumVal(lhs.value * rhs.value);
    }

    if constexpr(std::is_same_v<T<L, R>, Div<L, R>>){
        auto lhs = evalExpr(e.lhs, env);
        auto rhs = evalExpr(e.rhs, env);
        return NumVal(lhs.value / rhs.value);
    }

    if constexpr(std::is_same_v<T<L, R>, Minus<L, R>>){
        auto lhs = evalExpr(e.lhs, env);
        auto rhs = evalExpr(e.rhs, env);
        return NumVal(lhs.value - rhs.value);
    }

    if constexpr(std::is_same_v<T<L, R>, Let<L, R>>){
        env[e.par] = evalExpr(e.lhs, env);
        return evalExpr(e.rhs, env);
    }

    if constexpr(std::is_same_v<T<L, R>, MultiLet<L, R>>){
        return evalExpr(e.rhs, e.params.zip(e.lhs).fold(env)(
            [&env, lambdaEval](Environment acc, auto elt){
                acc[elt.first] = lambdaEval(elt.second);
                return acc;
            }
        ));
    }


    throw std::runtime_error("Unknown type: " + std::string(typeid(T<L, R>).name()));
}


int main(){

    auto e = MultiLet(Bector<std::string>("x", "y", "z"), Bector(Num(5), Num(7), Num(3)),Plus(Var("x"), Mul(Var("y"), Var("z"))));

    Environment env;

    // e.params.zip(e.lhs).fold(env)(
    //     [env](Environment acc, auto elt){
    //         return acc.insert({elt.first, evalExpr(elt.second, env)});
    //     }
    // );

    // Multi let x, y, z = 5, 7, 3 in x + y * z;


    std::cout << (evalExpr(e, env)) << std::endl;


    return 0;
}