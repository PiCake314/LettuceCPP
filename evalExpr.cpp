#include <iostream>
#include <unordered_map>
#include <fstream>
#include "Expr.hpp"
#include "lexer.cpp"

using Environment = std::unordered_map<std::string, Num>;
// using AST = std::vector<Expr*>;



Num evalExpr(const Expr* e, Environment env){
    if(const auto n = dynamic_cast<const Num*>(e)){
        return *n;
    }
    else if(const auto* v = dynamic_cast<const Var*>(e)){
        return env[v->name];
    }
    else if(const auto p = dynamic_cast<const Plus*>(e)){
        return evalExpr(p->lhs, env).value + evalExpr(p->rhs, env).value;
    }
    else if(const auto m = dynamic_cast<const Mult*>(e)){
        return evalExpr(m->lhs, env).value * evalExpr(m->rhs, env).value;
    }
    else if(const auto d = dynamic_cast<const Div*>(e)){
        return evalExpr(d->lhs, env).value / evalExpr(d->rhs, env).value;
    }
    else if(const auto m = dynamic_cast<const Minus*>(e)){
        return evalExpr(m->lhs, env).value - evalExpr(m->rhs, env).value;
    }
    else if(const auto l = dynamic_cast<const Let*>(e)){
        env[l->name] = evalExpr(l->value, env);
        return evalExpr(l->body, env);
    }
    else if(const auto ml = dynamic_cast<const MultiLet*>(e)){
        for (int i = 0; i < ml->names.size(); i++){
            env[ml->names[i]] = evalExpr(ml->values[i], env);
        }
        return evalExpr(ml->body, env);
    }

    else if(auto p = dynamic_cast<const Paren*>(e)){
        return evalExpr(p->expr, env);
    }

    // logical operators
    else if(const auto lt = dynamic_cast<const LessThan*>(e)){
        return evalExpr(lt->lhs, env).value < evalExpr(lt->rhs, env).value;
    }
    else if(const auto gt = dynamic_cast<const GreaterThan*>(e)){
        return evalExpr(gt->lhs, env).value > evalExpr(gt->rhs, env).value;
    }
    else if(const auto lteq = dynamic_cast<const LessThanEq*>(e)){
        return evalExpr(lteq->lhs, env).value <= evalExpr(lteq->rhs, env).value;
    }
    else if(const auto gteq = dynamic_cast<const GreaterThanEq*>(e)){
        return evalExpr(gteq->lhs, env).value >= evalExpr(gteq->rhs, env).value;
    }
    else if(const auto eq = dynamic_cast<const Equal*>(e)){
        return evalExpr(eq->lhs, env).value == evalExpr(eq->rhs, env).value;
    }
    else if(const auto neq = dynamic_cast<const NotEqual*>(e)){
        return evalExpr(neq->lhs, env).value != evalExpr(neq->rhs, env).value;
    }
    else if(const auto and_ = dynamic_cast<const And*>(e)){
        return evalExpr(and_->lhs, env).value && evalExpr(and_->rhs, env).value;
    }
    else if(const auto or_ = dynamic_cast<const Or*>(e)){
        return evalExpr(or_->lhs, env).value || evalExpr(or_->rhs, env).value;
    }
    else if(const auto not_ = dynamic_cast<const Not*>(e)){
        return !evalExpr(not_->expr, env).value;
    }

    // if-then-else
    else if(const IfThenElse* ite = dynamic_cast<const IfThenElse*>(e)){
        if(evalExpr(ite->cond, env).value){
            return evalExpr(ite->then, env);
        }
        else{
            return evalExpr(ite->els, env);
        }
    }
    else{
        throw std::runtime_error("Unknown expression type");
    }
}



void clean(Expr* e){

}

int main(){
    std::ifstream ifs("main.pie");
    std::string code
    {(std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>())};



    Expr* e = lexer(code);
    std::cout << *e << std::endl;

    Environment env;
    Num v = evalExpr(e,  env);
    
    std::cout << v.value << std::endl;
    return 0;
}
