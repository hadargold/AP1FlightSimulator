//
// Created by yuval on 11/6/19.
//

#include "ex1.h"
#include "Interpreter.h"
#include <regex>
#include <queue>
#include <vector>
#include <map>


using namespace std;

void changeToReverse(string str, queue<string>* output, stack<string>* operatorStack);
Expression *createExp(queue<string>* output);
bool isOperator(string str);
string findNum(string str);
void fromStackToQueue (queue<string>** output, stack<string>** operatorStack);
bool varIsValid(string token);
bool numIsValid(string token);
void setVariablesByMapOfVars(unordered_map<string,Variable*> nameOfVarToVariableMap);



// replace minus and plus before numbers and before ()
// return true if the string was changed in order to change all parts of it
bool replaceString(string* str) {
    for (size_t i = 0 ; i < str->length() ; i ++) {
        if ((*str)[i] == '+') {
            // if there is not  a number before
            if (i==0) {
                *str =  "(0+1)*" + str->substr(i+1);
                return true;
            } else if ((*str)[i-1] == '(' || (*str)[i-1] == '/' || (*str)[i-1] == '*') {
                *str = (*str).substr(0,i) + "(0+1)*" + (*str).substr(i+1);
                return true;
            }
        } else if ((*str)[i] == '-'){
            // if there is not  a number before
            if (i==0) {
                *str =  "(0-1)*" + str->substr(i+1);
                return true;
            } else if ((*str)[i-1] == '(' || (*str)[i-1] == '/' || (*str)[i-1] == '*') {
                *str = str->substr(0,i) + "(0-1)*" + str->substr(i+1);
                return true;
            }
        }
    }
    return false;
}


// this func is from stack overflow
string replaceAll(string str, string from, string to) {
    while (str.find(from) < str.length() ) { // if there is "from" in the string- replace it
        str = str.substr(0,str.find(from)) +"(" +to +")" + str.substr(str.find(from) + from.length() );
    }
    return str;
}

string replaceVar(string str, map< string, string >* varMap) {
    map<string, string >::iterator it;
    for ( it = varMap->begin(); it != varMap->end(); it++ )
    {
        if (str.find(it->first) < str.length()) {
            str = replaceAll(str, it->first, it->second);
        }
    }
    return str;
}

//return true if there is letters that are not allowed.
bool containsWrong (string* string1) {
    std::regex re("[^0-9|.|*|\\/|+|(|)|-]+");
    std::smatch match;
    return (std::regex_search(*string1, match, re));
}

// return false if the is a minus before variable without ()
void checkMinus (string var) {
    if (var[0] == '-') {
        string afterMinus(1, var[1]);
        regex letter("[A-z]");
        smatch match;
        if (regex_search(afterMinus, match, letter)) {
            throw "bad input";
        }
    }
}


// interprets the string
Expression *Interpreter::interpret(string str) {
    //checkMinus(str);
    if (!this->variables.empty()) {
        str = replaceVar(str, &this->variables);
    }
    bool changed = true;
    while (changed) {
        changed = replaceString(&str);
    }
    if (containsWrong(&str)) {
        throw "bad input";
    }
    queue<string> output;
    stack<string> operatorStack;
    // insert the reverse polish to the output queue.
    changeToReverse(str, &output, &operatorStack);
    Expression *e = createExp(&output);
    return e;
}

// inserts the variables to map
void Interpreter::tokenToMap(string* token) { // for example x=4 -> x,4
    try {
        string delimiter = "=";
        string var = token->substr(0, token->find(delimiter));
        if (var.length() == 0 || !varIsValid(var)) {
            throw "bad input";
        }
        string num = token->substr(token->find(delimiter) + 1);
        if (num.length() == 0 || !numIsValid(num)) {
            throw "bad input";
        }
        double number = stod(num);
        string strNum = to_string(number);
        (this->variables)[var] = strNum;
    } catch (exception exc) {
        throw ("bad input");
    }
}

// return true if the name of the variable is valid
bool varIsValid(string token) {
    char c = token[0];
    string first (1, c);
    regex firstChar("[A-z]");
    smatch match;
    if (regex_search(first, match, firstChar)) {
        regex other("[^0-9|[A-z]|_]+");
        if (regex_search(token, match, other)) {
            return false;
        }
    } else { // if the name of the string doesnt start with capital letter
        return false;
    }
    return true;
}


// return true if the value of the variable is valid
bool numIsValid(string token) {
    // if the problem is not . in the beginning the "stod" will return exception
    if (token[0]== '.') {
        return false;
    } else {
        return true;
    }
}

// parses the string to variables and their values and insert them into a map.
void Interpreter::setVariables(string var) {
    string delimiter = ";";
    string token;
    while (var.length() > 0) {
        if (var.find(';') < var.length()) {
            token = var.substr(0, var.find(delimiter));
            var = var.substr(var.find(delimiter) + 1);
        } else {  // ";" is not in var
            token = var;
            var = "";
        }
        this->tokenToMap(&token);
    }
}

void Interpreter::setVariablesByMapOfVars(unordered_map<string,Variable*> nameOfVarToVariableMap) {
    unordered_map<string, Variable*>::iterator it;
    for (it = nameOfVarToVariableMap.begin(); it != nameOfVarToVariableMap.end(); it++)
    {
        (this->variables)[it->first] = to_string(it->second->getValue());
    }
}



// destructor
Interpreter::~Interpreter() {
}

//return true if the fist char is an operator
bool isOperator(string str) {
    return (str[0] == '+' || str[0] == '*' || str[0] == '-' || str[0] == '/');
}

// return true if the top operator in the stack has higher precedence then the new operator
bool topIsHigherPre(char oper, string top) {
    return (oper == '+' || oper == '-') && (top == "*" || top == "/");
}

// this function return the number in the beginning of the string
string findNum(string str) {
    std::regex re("[0-9|\\.]+");
    std::smatch match;
    if (std::regex_search(str, match, re)) {
        return match.str();
    } else {
        return "";
    }
}

// this function get the string of the expression and change is to reverse polish in a queue
void changeToReverse(string str, queue<string> *output, stack<string> *operatorStack) {
    while (str.length() > 0) {
        // while the first character in the string is operator
        if (isOperator(str)) {
            char oper = str[0];
            // if the operator in the top has higher or equal precedence and is not "("
            while (!operatorStack->empty() && topIsHigherPre(oper, operatorStack->top()) &&
                   operatorStack->top() != "(") {
                output->push(operatorStack->top());
                operatorStack->pop();
            }
            string operS(1, oper);
            operatorStack->push(operS);
            str = str.substr(1);
        } else if (str[0] == '(') {
            str = str.substr(1);
            operatorStack->push("(");
        } else if (str[0] == ')') {
            while (!operatorStack->empty() && operatorStack->top() != "(") {
                output->push(operatorStack->top());
                operatorStack->pop();
            }
            if (!operatorStack->empty() && operatorStack->top() == "(") {
                operatorStack->pop();
            } else if (operatorStack->empty()) {
                throw "bad input";
            }
            str = str.substr(1);
        } else { // the first char in the string i a number
            string num = findNum(str);
            if (num == "") {
                throw "bad input";
            }
            output->push(num);
            str = str.substr(num.length());
        }
    } // str.length() == 0 :
    fromStackToQueue(&output, &operatorStack);
}

// this function moves all the elements from the
void fromStackToQueue(queue<string> **output, stack<string> **operatorStack) {
    while (!(*operatorStack)->empty()) {
        (*output)->push((*operatorStack)->top());
        (*operatorStack)->pop();
    }
}

// return true if the front of the queue is a number
bool frontIsNumber(string front) {
    return !(front == "+" || front == "-" || front == "*" || front == "/");
}

// this function create expression from the reverse polish
Expression *createExp(queue<string> *output) {
    Expression *tempExp = nullptr;
    Value* tempNum = nullptr;
    if (output->size() == 1 && frontIsNumber(output->front())) {
        double num = stod(output->front());
        return new Value(num);
    }
    try {
        stack<Value> numStack;
        double res = 0;
        while (!output->empty()) {

            if (frontIsNumber(output->front())) {
                double num = stod(output->front());
                tempNum = new Value(num);
                output->pop();
                numStack.push(*tempNum);
                delete(tempNum);
                tempNum = nullptr;
            } else { // the front is an operator
                if (numStack.empty()) {
                    throw "bad input";
                }
                Value *r = new Value(numStack.top());
                numStack.pop();
                if (numStack.empty()) {
                    throw "bad input";
                }
                Value *l = new Value(numStack.top());
                numStack.pop();
                if (output->front() == "+") {
                    tempExp = new Plus(l, r);
                    numStack.push(tempExp->calculate());
                    output->pop();
                } else if (output->front() == "-") {
                    tempExp = new Minus(l, r);
                    numStack.push(tempExp->calculate());
                    output->pop();
                } else if (output->front() == "*") {
                    tempExp = new Mul(l, r);
                    numStack.push(tempExp->calculate());
                    output->pop();
                } else if (output->front() == "/") {
                    if (r->calculate() == 0) {
                        delete (r);
                        delete (l);
                        tempNum = nullptr;
                        throw "bad input";
                    }
                    tempExp = new Div(l, r);
                    numStack.push(tempExp->calculate());
                    output->pop();
                }
                res = tempExp->calculate();
                delete tempExp;
                tempExp = nullptr;
            }
        }
        numStack.pop();
        if (!numStack.empty()) {
            throw "bad input";
        }
        return new Value(res);
    } catch (exception e) {
        delete tempNum ;
        delete tempExp;
        throw "bad input";
    }
}