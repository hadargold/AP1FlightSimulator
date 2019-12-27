//
// Created by yuval on 11/6/19.
//

#ifndef UNTITLED_EX1_H
#define UNTITLED_EX1_H
#include "Expression.h"
#include <iostream>
#include <map>
using namespace std;

class Variable : public Expression {
private:
    string nameAccordingToSim;
    int direction;
    double value;
public:
    Variable(string name, double value, int direction);
    string getName() {
        return nameAccordingToSim;
    }
    double getValue() {
        return value;
    }
    int getDirection() {
        return direction;
    }
    Variable& operator++();
    Variable& operator--();
    Variable& operator+=(double);
    Variable& operator-=(double);
    Variable & operator++(int);
    Variable & operator--(int);
    double calculate() override;
    ~Variable();

};

class UnaryOperator : public Expression {
protected:
    Expression* exp;
public:
    explicit UnaryOperator(Expression *exp);
    ~UnaryOperator() override;
};

class UPlus : public UnaryOperator {
public:
    double calculate() override;
    UPlus(Expression *exp);
    ~UPlus() override;
};

class UMinus : public UnaryOperator {
public:
    UMinus(Expression *exp);
    double calculate() override;
    ~UMinus() override = default;
};

class Value : public Expression {
private:
    const double val;
public:
    double calculate() override;
    Value(const double val);
    ~Value() override = default;
};

class BinaryOperator : public Expression {
protected:
    Expression* left;
    Expression* right;
public:
    BinaryOperator(Expression *left, Expression *right);
    ~BinaryOperator();
};

class Plus : public BinaryOperator {
public:
    Plus(Expression *left, Expression *right);
    double calculate() override;
};

class Minus : public BinaryOperator {
public:
    double calculate() override;
    Minus(Expression *left, Expression *right);
};

class Mul : public BinaryOperator {
public:
    Mul(Expression *left, Expression *right);
    double calculate() override;
};

class Div : public BinaryOperator {
public:
    Div(Expression *left, Expression *right);
    double calculate() override;
};

class Interpreter {
private:
    map< string, string > variables;
public:
    void tokenToMap(string* token);
    Expression* interpret(string exp);
    void setVariables(string var);
    ~Interpreter();
};


#endif //UNTITLED_EX1_H