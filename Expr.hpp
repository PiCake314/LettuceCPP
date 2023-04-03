#pragma once

#include <ostream>
#include "../Bector/Bector.hpp"

// struct Expr{ virtual ~Expr() = default; };


// struct Num : Expr{
//     double value;
//     Num(double v) : value(v) {};
// };

// struct Var : Expr{
//     std::string name;
//     Var(std::string n) : name(n) {};
// };

// struct Plus : Expr{
//     Expr lhs;
//     Expr rhs;
//     Plus(Expr l, Expr r) : lhs(l), rhs(r) {};
// };

// struct Mult : Expr{
//     Expr lhs;
//     Expr rhs;
//     Mult(Expr l, Expr r) : lhs(l), rhs(r) {};
// };

// struct Div : Expr{
//     Expr lhs;
//     Expr rhs;
//     Div(Expr l, Expr r) : lhs(l), rhs(r) {};
// };

// struct Minus : Expr{
//     Expr lhs;
//     Expr rhs;
//     Minus(Expr l, Expr r) : lhs(l), rhs(r) {};
// };

// struct Let : Expr{
//     std::string name;
//     Expr value;
//     Expr body;
//     Let(std::string n, Expr v, Expr b) : name(n), value(v), body(b) {};
// };

// struct MultiLet : Expr{
//     Bector<std::string> names;
//     Bector<Expr> values;
//     Expr body;
//     MultiLet(Bector<std::string> n, Bector<Expr> v, Expr b) : names(n), values(v), body(b) {};
// };


struct NumVal{
    double value;
    NumVal() : value(0) {}; // for typedef
    NumVal(double v) : value(v) {};

    friend std::ostream& operator<<(std::ostream& os, NumVal const& n){
        return os << "NumVal(" << n.value << ")";
    }
};
