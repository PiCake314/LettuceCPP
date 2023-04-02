#include <iostream>
#include <unordered_map>
// #include <variant>
#include <any>
#include "Expr.hpp"


typedef std::unordered_map<std::string, NumVal> Environment;

NumVal evalExpr(Expr *e, Environment env){

    if(auto *num = dynamic_cast<Num*>(e)){
        return NumVal(num->value);
    }
    else if(auto *var = dynamic_cast<Var*>(e)){
        return env[var->name];
    }
    else if(auto *add = dynamic_cast<Plus*>(e)){
        auto l = evalExpr(add->lhs, env);
        auto r = evalExpr(add->rhs, env);

        return NumVal(l.value + r.value);
    }
    else if(auto *sub = dynamic_cast<Minus*>(e)){
        auto l = evalExpr(sub->lhs, env);
        auto r = evalExpr(sub->rhs, env);

        return NumVal(l.value - r.value);
    }
    else if(auto *div = dynamic_cast<Div*>(e)){
        auto l = evalExpr(div->lhs, env);
        auto r = evalExpr(div->rhs, env);

        return NumVal(l.value / r.value);
    }
    else if(auto *mul = dynamic_cast<Mult*>(e)){
        auto l = evalExpr(mul->lhs, env);
        auto r = evalExpr(mul->rhs, env);

        return NumVal(l.value * r.value);
    }
    else if(auto let = dynamic_cast<Let*>(e)){
        env[let->name] = evalExpr(let->value, env);
        return evalExpr(let->body, env);
    }
    else if(auto multLet = dynamic_cast<MultiLet*>(e)){
        Environment newEnv = multLet->names.zip(multLet->values).fold<Environment>(env)(
            [](Environment env, std::pair<std::string, Expr*> nameValue){
                env[nameValue.first] = evalExpr(nameValue.second, env);
                return env;
            }
        );

        return evalExpr(multLet->body, newEnv);
    }


    throw std::runtime_error("Unknown type");
    return NumVal(0);
}


int main(){
    // ALT BRANCH
    
    // write a test for MultiLet

    Expr *e = new MultiLet(Bector<std::string>("x", "y", "z"), Bector<Expr*>(new Plus(new Num(5), new Num(3)), new Mult(new Num(7), new Num(3)), new Num(10)), new Plus(new Var("x"), new Var("y")));


    Environment env;

    std::cout << evalExpr(e, env) << std::endl;


    return 0;
}