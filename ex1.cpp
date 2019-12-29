//
// Created by yuval on 11/6/19.
//

#include "ex1.h"

#include <utility>
using namespace std;


Variable& Variable::operator++() {
    this->value += 1;
    return *this;
}

Variable& Variable::operator--() {
    this->value -= 1;
    return *this;
}

Variable& Variable::operator+=(double num) {
    this->value += 1;
    return *this;
}

Variable& Variable::operator-=(double num) {
    this->value += 1;
    return *this;
}

Variable& Variable::operator++(int num) {
    this->value += 1;
    return *this;
}
Variable & Variable::operator--(int num) {
    auto* temp = new Variable(this->nameAccordingToSim, this->value, this->direction);
    this->value -= num;
    return *temp;
}
double Variable::calculate() {
    return this->value;
}

Variable::Variable(string name, double value, int direction) : name(std::move(name)), value(value) {}

Variable::~Variable() = default;


UnaryOperator::UnaryOperator(Expression *exp) : exp(exp) {}

UnaryOperator::~UnaryOperator() {
    delete (exp);
}

UPlus::UPlus(Expression *exp) : UnaryOperator(exp) {}

double UPlus::calculate() {
    return this->exp->calculate();
}

UPlus::~UPlus() {
}

UMinus::UMinus(Expression *exp) : UnaryOperator(exp) {}

double UMinus::calculate() {
    return (this->exp->calculate())*-1;
}

Value::Value(const double val) : val(val) {}

double Value::calculate() {
    return this->val;
}

BinaryOperator::BinaryOperator(Expression *left, Expression *right) : left(left), right(right) {}
BinaryOperator::~BinaryOperator() {
    delete(left);
    delete(right);
}

Plus::Plus(Expression *left, Expression *right) : BinaryOperator(left, right) {}


double Plus::calculate() {
    return this->left->calculate() + this->right->calculate();
}

Minus::Minus(Expression *left, Expression *right) : BinaryOperator(left, right) {}


double Minus::calculate() {
    return this->left->calculate() - this->right->calculate();
}

Mul::Mul(Expression *left, Expression *right) : BinaryOperator(left, right) {}




double Mul::calculate() {
    double  l = this->left->calculate();
    return this->left->calculate() * this->right->calculate();
}

Div::Div(Expression *left, Expression *right) : BinaryOperator(left, right) {}


double Div::calculate() {
    if (this->right->calculate() == 0) {
        throw "bad input";
    }
    return this->left->calculate() / this->right->calculate();
}