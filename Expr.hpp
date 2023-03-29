#pragma once

#include <ostream>
#include "../mylibs/Bector/Bector.hpp"

#define case template <typename L, typename R>

struct Expr{};

template <typename L = Expr, typename R = Expr>
struct Num : Expr{
    std::string name;
    double value;
    Num() : value(0) {}; // for Bector initialization
    Num(double v) : value(v) {};
};


template <typename L = Expr, typename R = Expr>
struct Var : Expr{
    std::string name;
    double value;
    Var(std::string n) : name(n) {};
};

case struct Plus : Expr{
    // const L& lhs;
    L lhs;
    // const R& rhs;
    R rhs;
    double value;
    std::string name;

    Plus() : lhs(Num(0)), rhs(Num(0)) {}; // for Bector initialization
    Plus(L const& l, R const& r) : lhs(l), rhs(r) {};
};

case struct Mult : Expr{
    // const L& lhs;
    L lhs;
    // const R& rhs;
    R rhs;
    double value;
    std::string name;

    Mult(L const& l, R const& r) : lhs(l), rhs(r) {};
};

case struct Div : Expr{
    // const L& lhs;
    L lhs;
    // const R& rhs;
    R rhs;
    double value;
    std::string name;

    Div(L const& l, R const& r) : lhs(l), rhs(r) {};
};

case struct Minus : Expr{
    // const L& lhs;
    L lhs;
    // const R& rhs;
    R rhs;
    double value;
    std::string name;

    Minus(L const& l, R const& r) : lhs(l), rhs(r) {};
};

case struct Let : Expr{
    std::string par;
    // const L& lhs;
    L lhs;
    // const R& rhs;
    R rhs;
    double value;
    std::string name;

    Let(std::string n, L const& l, R const& r) : par(n), lhs(l), rhs(r) {};
};

case struct MultiLet : Expr{
    Bector<std::string> params;
    Bector<L> lhs;
    // const R& rhs;
    R rhs;
    double value;
    std::string name;

    MultiLet(Bector<std::string> n, Bector<L> l, R const& r) : params(n), lhs(l), rhs(r) {};
};


struct NumVal{
    double value;
    NumVal() : value(0) {}; // for typedef
    NumVal(double v) : value(v) {};

    friend std::ostream& operator<<(std::ostream& os, NumVal const& n){
        return os << "NumVal(" << n.value << ")";
    }
};
