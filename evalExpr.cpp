#include <iostream>
#include <unordered_map>
#include "Expr.hpp"
#include "../Cool-Libs/mpark/patterns.hpp"

typedef std::unordered_map<std::string, NumVal> Environment;

class Num{
public:
    double value;
    // Num(double v) : value(v) {};
    Num operator=(double v){
        value = v;
        return *this;
    }
};


// template <typename T>
NumVal evalExpr(Num e, Environment env){
    using namespace mpark::patterns;
    IDENTIFIERS(x);

    return match(e)(
        pattern(ds(x)) = [](auto &&x){
            std::cout << "X: " << x << std::endl;
            return NumVal(10);
         },
        pattern(_) = [](){ return NumVal(0); }
    );
    



    throw std::runtime_error("Unknown type");
    return NumVal(0);
}


int main(){
    // Expr e = MultiLet(Bector<std::string>("x", "y", "z"), Bector<Expr>(Plus(Num(5), Num(3)), Mult(Num(7), Num(3)), Num(10)), Plus(Var("x"), Var("y")));
    auto e = Num(10);
    Environment env;


    std::cout << evalExpr(e, env) << std::endl;


    return 0;
}