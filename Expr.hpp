#pragma once

#include <ostream>
#include <vector>

struct Expr{
    virtual ~Expr() = default;
    virtual void print() = 0;
};


std::ostream& operator<<(std::ostream& os, Expr& e){
    e.print();
    return os;
}


struct Num : Expr{
    double value;
    Num() = default;
    Num(double v) : value(v) {};

    void print() override {
        std::cout << "Num(" << value << ")";
    }
    
};

struct Var : Expr{
    std::string name;
    Var(std::string n) : name(n) {};

    void print() override {
        std::cout << "Var(" << name << ")";
    }
};

struct Plus : Expr{
    Expr* lhs;
    Expr* rhs;
    Plus(Expr* l, Expr* r) : lhs(l), rhs(r) {};
    
    void print() override {
        std::cout << "Plus(";
        lhs->print();
        std::cout << ", ";
        rhs->print();
        std::cout << ")";
    }
};

struct Mult : Expr{
    Expr* lhs;
    Expr* rhs;
    Mult(Expr* l, Expr* r) : lhs(l), rhs(r) {};
    
    void print() override {
        std::cout << "Mult(";
        lhs->print();
        std::cout << ", ";
        rhs->print();
        std::cout << ")";
    }
};

struct Div : Expr{
    Expr* lhs;
    Expr* rhs;
    Div(Expr* l, Expr* r) : lhs(l), rhs(r) {};
    
    void print() override {
        std::cout << "Div(";
        lhs->print();
        std::cout << ", ";
        rhs->print();
        std::cout << ")";
    }
};

struct Minus : Expr{
    Expr* lhs;
    Expr* rhs;
    Minus(Expr* l, Expr* r) : lhs(l), rhs(r) {};
    
    void print() override {
        std::cout << "Minus(";
        lhs->print();
        std::cout << ", ";
        rhs->print();
        std::cout << ")";
    }
};

struct Let : Expr{
    std::string name;
    Expr* value;
    Expr* body;
    Let(std::string n, Expr* v, Expr* b) : name(n), value(v), body(b) {};
    
    void print() override {
        std::cout << "Let(" << name << ", ";
        value->print();
        std::cout << ", ";
        body->print();
        std::cout << ")";
    }
};

struct MultiLet : Expr{
    std::vector<std::string> names;
    std::vector<Expr*> values;
    Expr* body;
    MultiLet(std::vector<std::string> n, std::vector<Expr*> v, Expr* b) : names(n), values(v), body(b) {};
    
    void print() override {
        std::cout << "MultiLet(";
        for (int i = 0; i < names.size(); i++){
            std::cout << names[i] << ", ";
        }
        std::cout << ", ";
        for (int i = 0; i < values.size(); i++){
            values[i]->print();
            std::cout << ", ";
        }
        std::cout << ", ";
        body->print();
        std::cout << ")";
    }
};


struct Paren : Expr{
    Expr* expr;
    Paren(Expr* e) : expr(e) {};
    
    void print() override {
        std::cout << "Paren(";
        expr->print();
        std::cout << ")";
    }
};


struct LessThan : Expr{
    Expr* lhs;
    Expr* rhs;
    LessThan(Expr* l, Expr* r) : lhs(l), rhs(r) {};
    
    void print() override {
        std::cout << "LessThan(";
        lhs->print();
        std::cout << ", ";
        rhs->print();
        std::cout << ")";
    }
};


struct GreaterThan : Expr{
    Expr* lhs;
    Expr* rhs;
    GreaterThan(Expr* l, Expr* r) : lhs(l), rhs(r) {};
    
    void print() override {
        std::cout << "GreaterThan(";
        lhs->print();
        std::cout << ", ";
        rhs->print();
        std::cout << ")";
    }
};


struct LessThanEq : Expr{
    Expr* lhs;
    Expr* rhs;
    LessThanEq(Expr* l, Expr* r) : lhs(l), rhs(r) {};
    
    void print() override {
        std::cout << "LessThanEq(";
        lhs->print();
        std::cout << ", ";
        rhs->print();
        std::cout << ")";
    }
};

struct GreaterThanEq : Expr{
    Expr* lhs;
    Expr* rhs;
    GreaterThanEq(Expr* l, Expr* r) : lhs(l), rhs(r) {};
    
    void print() override {
        std::cout << "GreaterThanEq(";
        lhs->print();
        std::cout << ", ";
        rhs->print();
        std::cout << ")";
    }
};

struct Equal : Expr{
    Expr* lhs;
    Expr* rhs;
    Equal(Expr* l, Expr* r) : lhs(l), rhs(r) {};
    
    void print() override {
        std::cout << "Equal(";
        lhs->print();
        std::cout << ", ";
        rhs->print();
        std::cout << ")";
    }
};

struct NotEqual : Expr{
    Expr* lhs;
    Expr* rhs;
    NotEqual(Expr* l, Expr* r) : lhs(l), rhs(r) {};
    
    void print() override {
        std::cout << "NotEqual(";
        lhs->print();
        std::cout << ", ";
        rhs->print();
        std::cout << ")";
    }
};


struct And : Expr{
    Expr* lhs;
    Expr* rhs;
    And(Expr* l, Expr* r) : lhs(l), rhs(r) {};
    
    void print() override {
        std::cout << "And(";
        lhs->print();
        std::cout << ", ";
        rhs->print();
        std::cout << ")";
    }
};


struct Or : Expr{
    Expr* lhs;
    Expr* rhs;
    Or(Expr* l, Expr* r) : lhs(l), rhs(r) {};
    
    void print() override {
        std::cout << "Or(";
        lhs->print();
        std::cout << ", ";
        rhs->print();
        std::cout << ")";
    }
};


struct Not : Expr{
    Expr* expr;
    Not(Expr* e) : expr(e) {};
    
    void print() override {
        std::cout << "Not(";
        expr->print();
        std::cout << ")";
    }
};


struct IfThenElse : Expr{
    Expr* cond;
    Expr* then;
    Expr* els;
    IfThenElse(Expr* c, Expr* t, Expr* e) : cond(c), then(t), els(e) {};
    
    void print() override {
        std::cout << "IfThenElse(";
        cond->print();
        std::cout << ", ";
        then->print();
        std::cout << ", ";
        els->print();
        std::cout << ")";
    }
};
