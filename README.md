# Lettuce - Reinventing the wheel in C++

Lettuce is a programming language that is used by CSCI 3155 as a project for the course. It is a simple language that is used to demonstrate the concepts of compilers and interpreters. 3155 students uses a language called Scala to implement the compiler and interpreter for Lettuce. In this project, we will be using C++ instead.


## Expr.hpp
This file holds the implementation of the Expr "trait" which is used to represent expressions in Lettuce. It also holds the implementation of all the other classes that inherit from Expr. These classes are used to represent the different types of expressions in Lettuce.

### We have implemented the following classes:
- Expr
- Num
- Var
- Plus
- Mult
- Div
- Minus
- Let
- MultiLet

## evalExpr.cpp
This file holds the implementation of the evalExpr function. This function is used to evaluate an expression in Lettuce. It takes in an Expr object and returns a ```NumVal(d)``` object.


## Syntac Example
```
Let("x", Num(5), Plus(Var("x"), Num(2)))
```
## Output
```
NumVal(7)
```


### Requirements

- C++ 20 or higher
- g++ 14 or higher (recommended)