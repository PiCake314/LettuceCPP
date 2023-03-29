#include <iostream>
#include <unordered_map>
// #include <variant>
#include <any>
#include "Expr.hpp"


typedef std::unordered_map<std::string, NumVal> Environment;


// NumVal evalExpr(std::any e, Environment env){
//     if(e.type() == typeid(NumVal)){
//         return std::any_cast<NumVal>(e);
//     }

//     if(e.type() == typeid(Var<>)){
//         if(env.find(std::any_cast<Var<>>(e).name) != env.end()){
//             return env.at(std::any_cast<Var<>>(e).name);
//         }
//         throw std::runtime_error("Variable not found");
//     }


//     try{
//         auto expr = std::any_cast<Plus<>>(e);
//         auto lhs = evalExpr(std::any_cast<Plus<>>(e).lhs, env);
//         auto rhs = evalExpr(std::any_cast<Plus>(e).rhs, env);
//         return NumVal(lhs.value + rhs.value);
//     }
//     catch(const std::exception& e){}
    

//     if(e.type() == typeid(Mult)){
//         auto lhs = evalExpr(std::any_cast<Mult>(e).lhs, env);
//         auto rhs = evalExpr(std::any_cast<Mult>(e).rhs, env);
//         return NumVal(lhs.value * rhs.value);
//     }
//     if(e.type() == typeid(Div)){
//         auto lhs = evalExpr(std::any_cast<Div>(e).lhs, env);
//         auto rhs = evalExpr(std::any_cast<Div>(e).rhs, env);
//         return NumVal(lhs.value / rhs.value);
//     }
//     if(e.type() == typeid(Minus)){
//         auto lhs = evalExpr(std::any_cast<Minus>(e).lhs, env);
//         auto rhs = evalExpr(std::any_cast<Minus>(e).rhs, env);
//         return NumVal(lhs.value - rhs.value);
//     }
//     if(e.type() == typeid(Let)){
//         auto lhs = evalExpr(std::any_cast<Let>(e).lhs, env);
//         env[std::any_cast<Let>(e).par] = lhs;
//         return evalExpr(std::any_cast<Let>(e).rhs, env);
//     }
//     if(e.type() == typeid(MultiLet)){
//         auto lhs = evalExpr(std::any_cast<MultiLet>(e).lhs, env);
//         for(int i = 0; i < std::any_cast<MultiLet>(e).params.size(); i++){
//             env[std::any_cast<MultiLet>(e).params.at(i)] = lhs.at(i);
//         }
//         return evalExpr(std::any_cast<MultiLet>(e).rhs, env);
//     }
//     throw std::runtime_error("Expression not found");
// }



template <template <typename, typename> class T, typename L, typename R>
requires std::is_base_of<Expr, T<L, R>>::value
NumVal evalExpr(T<L, R> e, Environment env){

    if constexpr(std::is_same_v<T<L, R>, Num<L, R>>){
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
    
    if constexpr(std::is_same_v<T<L, R>, Mult<L, R>>){
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
            [env](Environment acc, std::pair<std::string, L> elt){

                

                acc[elt.first] = evalExpr(elt.second, env);
                return acc;
            }
        ));





        // return evalExpr(e.rhs, e.params.zip(e.lhs).fold(env)(
        //     [env](Environment acc, std::pair<std::string, L> elt){
        //         acc[elt.first] = evalExpr(elt.second, env);
        //         return acc;
        //     }
        // ));
    }


    throw std::runtime_error("Unknown type: " + std::string(typeid(T<L, R>).name()));

    return NumVal(0);
}


int main(){
    // DEV BRANCH
    // auto e = MultiLet(Bector<std::string>("x","y","z","w"), Bector(Plus(NumVal(7), NumVal(3)), NumVal(10.0), NumVal(10.0), NumVal(20.0)), MultiLet(Bector<std::string>(), Bector<Expr>(), Let("w", Var("w"), Mult(Var("x"), Plus(Var("y"), Var("w"))))));

    // Bector b = Bector<std::any>(Plus(NumVal(7), NumVal(3)), NumVal(10.0), NumVal(10.0), NumVal(20.0));
    // auto e = MultiLet(Bector<std::string>("x","y","z","w"), b, MultiLet(Bector<std::string>(), Bector<std::any>(), Let("w", Var("w"), Mult(Var("x"), Plus(Var("y"), Var("w"))))));
 

    auto  e = MultiLet(Bector<std::string>("x", "y", "z"), Bector(Num(5), Num(7), Num(3)), Plus(Var("x"), Mult(Var("y"), Var("z"))));
    Environment env;

    std::cout << evalExpr(e, env) << std::endl;


    return 0;
}