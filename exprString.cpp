#include <iostream>
#include <unordered_map>
#define case template <typename L, typename R>


struct Expr{};

template <typename L = Expr, typename R = Expr>
struct Num : Expr{
    double value;
    Num(double v) : value(v) {};
};

case struct Var : Expr{
    std::string name;
    Var(std::string n) : name(n) {};
};

case struct Plus : Expr{
    L const& lhs;
    R const& rhs;

    Plus(L const& l, R const& r) : lhs(l), rhs(r) {};
};

case struct Mul : Expr{
    L const& lhs;
    R const& rhs;

    Mul(L const& l, R const& r) : lhs(l), rhs(r) {};
};

case struct Div : Expr{
    L const& lhs;
    R const& rhs;

    Div(L const& l, R const& r) : lhs(l), rhs(r) {};
};

case struct Minus : Expr{
    L const& lhs;
    R const& rhs;

    Minus(L const& l, R const& r) : lhs(l), rhs(r) {};
};


template <template <typename, typename> class T, typename L, typename R>
requires std::is_base_of<Expr, T<L, R>>::value
std::string evalExpr(T<L, R> e) noexcept {

    if constexpr(std::is_same_v<T<L, R>, Num<L, R>>)
        return std::to_string(e.value);

    else if constexpr(std::is_same_v<T<L, R>, Plus<L, R>>)
        return "(" + evalExpr(e.lhs) + " + " + evalExpr(e.rhs) + ")";

    else if constexpr(std::is_same_v<T<L, R>, Mul<L, R>>)
        return "(" + evalExpr(e.lhs) + " * " + evalExpr(e.rhs) + ")";

    else if constexpr(std::is_same_v<T<L, R>, Div<L, R>>)
        return "(" + evalExpr(e.lhs)+ "/" + evalExpr(e.rhs) + ")";

    else if constexpr(std::is_same_v<T<L, R>, Minus<L, R>>)
        return "(" + evalExpr(e.lhs) + " - " + evalExpr(e.rhs) + ")";



    throw std::runtime_error("Unknown type");
}


int main(){

    std::unordered_map<std::string, double> env;

    auto e = Div(Plus(Num(5), Minus(Num(3), Num(2))), Mul(Num(2), Num(3)));
    std::cout << evalExpr(e) << std::endl;

    return 0;
}