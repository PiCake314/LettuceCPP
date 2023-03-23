#pragma once

#include <ostream>
// #include "../mylibs/Bector/Bector.hpp"

#define case template <typename L, typename R>

struct Expr{};

template <typename L = Expr, typename R = Expr>
struct Num : Expr{
    double value;
    Num(double v) : value(v) {};
};


template <typename L = Expr, typename R = Expr>
struct Var : Expr{
    std::string name;
    double value;

    Var(std::string n) : name(n) {};
};

case struct Plus : Expr{
    L const& lhs;
    R const& rhs;
    double value;

    Plus(L const& l, R const& r) : lhs(l), rhs(r) {};
};

case struct Mul : Expr{
    L const& lhs;
    R const& rhs;
    double value;

    Mul(L const& l, R const& r) : lhs(l), rhs(r) {};
};

case struct Div : Expr{
    L const& lhs;
    R const& rhs;
    double value;

    Div(L const& l, R const& r) : lhs(l), rhs(r) {};
};

case struct Minus : Expr{
    L const& lhs;
    R const& rhs;
    double value;

    Minus(L const& l, R const& r) : lhs(l), rhs(r) {};
};

case struct Let : Expr{
    std::string name;
    L const& lhs;
    R const& rhs;
    double value;

    Let(std::string n, L const& l, R const& r) : name(n), lhs(l), rhs(r) {};
};

// case struct MultiLet : Expr{
//     Bector<std::string> names;
//     Bector<L> lhs;
//     R const& rhs;

//     MultiLet(Bector<std::string> n, Bector<L> l, R const& r) : names(n), lhs(l), rhs(r) {};
// };


struct NumVal{
    double value;
    NumVal() : value(0) {}; // for typedef
    NumVal(double v) : value(v) {};

    friend std::ostream& operator<<(std::ostream& os, NumVal const& n){
        return os << "NumVal(" << n.value << ")";
    }
};


// Plus(Num(1), Mul(Num(2), Num(3))