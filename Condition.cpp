//
// Created by hadar on 12/29/19.
//

#include "Condition.h"
#include <iostream>
#include <string>
#include <vector>
#include "PrintCommand.h"
#include "VariableManager.h"
#include "Interpreter.h"
#include "SymbolTable.h"

Condition::Condition(vector <string> cond){
    this->condition = cond;
}

bool Condition::getResult(){
    return this->result;
}

void Condition::execute(int *it){
    if(condition.size() == 1)
    {
        this->result = (condition[0] == "1") ? true : false;
    }
    else {
        int i = 0;
        int conditionLocation;
        string left = "";
        string right = "";
        Expression *sideA, *sideB;
        while (condition[i] != "<" && condition[i] != ">"
        && condition[i] != "<=" && condition[i] != ">="
        && condition[i] != "!=" && condition[i] != "==")
        {
            left += condition[i];
            i++;
        }
        conditionLocation = i;
        while(i < condition.size()){
            right += condition[i];
        }

        Interpreter *stringToInterpretForConditionLeft = new Interpreter();
        SymbolTable *symbolTable = new SymbolTable();
        unordered_map<string, Variable *> nameOfVarToVariableMap = symbolTable->getMap();
        stringToInterpretForConditionLeft->setVariablesByMapOfVars(nameOfVarToVariableMap);
        Expression *expressionLeft = stringToInterpretForConditionLeft->interpret(left);

        Interpreter *stringToInterpretForConditionRight = new Interpreter();
        SymbolTable *symbolTableR = new SymbolTable();
        unordered_map<string, Variable *> nameOfVarToVariableMapR = symbolTable->getMap();
        stringToInterpretForConditionLeft->setVariablesByMapOfVars(nameOfVarToVariableMap);
        Expression *expressionRight = stringToInterpretForConditionLeft->interpret(right);

        if(condition[conditionLocation] == ">")
            result = expressionLeft->calculate() > expressionRight->calculate() ? true : false;
        if(condition[conditionLocation] == "<")
            result = expressionLeft->calculate() < expressionRight->calculate() ? true : false;
        if(condition[conditionLocation] == "!=")
            result = expressionLeft->calculate() != expressionRight->calculate() ? true : false;
        if(condition[conditionLocation] == "==")
            result = expressionLeft->calculate() == expressionRight->calculate() ? true : false;
        if(condition[conditionLocation] == "<=")
            result = expressionLeft->calculate() <= expressionRight->calculate() ? true : false;
        if(condition[conditionLocation] == ">=")
            result = expressionLeft->calculate() >= expressionRight->calculate() ? true : false;


    }

}