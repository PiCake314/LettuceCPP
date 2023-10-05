#include "Expr.hpp"


enum class Tokens{
    // Values
    Num,
    Var,

    // symbols
    Eq,
    Cmp,
    Lt,
    Ltq,
    Gt,
    Gtq,
    ParenOpen,
    ParenClose,

    // logic
    And,
    Or,
    Not,

    // arithmetic
    Add,
    Sub,
    Mult,
    Div,

    // keywords
    K_if,
    K_then,
    K_else

    // // other
    // Unknown

};



Expr* lexer(std::string code){
    for(int i = 0; i < code.size(); i++){
        if(std::isspace(code[i])){
            continue;
        }
        else if(std::isdigit(code[i])){
            continue;
        }
        else if(std::isalpha(code[i])){
            continue;
        }
        else if(code[i] == '='){
            int j = i+1;
            for(; code[j] != '\n';  j++);

            return new Let(code.substr(0, i), lexer(code.substr(i+1, j-i-1)), lexer(code.substr(j+1)));
        }
        else if(code[i] == ','){
            int j = i+1;
            for(; code[j] != '\n';  j++);

            return new MultiLet({code.substr(0, i)}, {lexer(code.substr(i+1, j-i-1))}, lexer(code.substr(j+1)));
        }

        // arithmetic operators
        else if(code[i] == '+'){
            return new Plus(lexer(code.substr(0, i)), lexer(code.substr(i+1)));
        }
        else if(code[i] == '-'){
            return new Minus(lexer(code.substr(0, i)), lexer(code.substr(i+1)));
        }
        else if(code[i] == '*'){
            return new Mult(lexer(code.substr(0, i)), lexer(code.substr(i+1)));
        }
        else if(code[i] == '/'){
            return new Div(lexer(code.substr(0, i)), lexer(code.substr(i+1)));
        }

        // logical operators
        else if(code[i] == '<' && code[i+1] == '='){
            return new LessThanEq(lexer(code.substr(0, i)), lexer(code.substr(i+2)));
        }
        else if(code[i] == '>' && code[i+1] == '='){
            return new GreaterThanEq(lexer(code.substr(0, i)), lexer(code.substr(i+2)));
        }
        else if(code[i] == '<'){
            return new LessThan(lexer(code.substr(0, i)), lexer(code.substr(i+1)));
        }
        else if(code[i] == '>'){
            return new GreaterThan(lexer(code.substr(0, i)), lexer(code.substr(i+1)));
        }
        else if(code[i] == '=' && code[i+1] == '='){
            return new Equal(lexer(code.substr(0, i)), lexer(code.substr(i+2)));
        }
        else if(code[i] == '!' && code[i+1] == '='){
            return new NotEqual(lexer(code.substr(0, i)), lexer(code.substr(i+2)));
        }
        else if(code[i] == '&' && code[i+1] == '&'){
            return new And(lexer(code.substr(0, i)), lexer(code.substr(i+2)));
        }
        else if(code[i] == '|' && code[i+1] == '|'){
            return new Or(lexer(code.substr(0, i)), lexer(code.substr(i+2)));
        }
        else if(code[i] == '!'){
            return new Not(lexer(code.substr(i+1)));
        }


        else if(code[i] == 'i' && code[i+1] == 'f'){
            int j = i+2;
            while(code[j] != 't'){
                j++;
            }
            return new IfThenElse(lexer(code.substr(i+2, j-i-2)), lexer(code.substr(j+1, code.size()-j-1)), lexer(code.substr(j+1, code.size()-j-1)));
        }
        else if(code[i] == '('){
            int j = i+1;
            int count = 1;
            while(count != 0){
                if(code[j] == '('){
                    count++;
                }
                else if(code[j] == ')'){
                    count--;
                }
                j++;
            }
            return new Paren(lexer(code.substr(i+1, j-i-2)));
        }
        else if(code[i] == ')'){
            throw std::runtime_error("Unexpected ')'");
        }
        else{
            throw std::runtime_error("Unknown expression: " + code);
        }
    }

    return new Num(std::stoi(code));
}