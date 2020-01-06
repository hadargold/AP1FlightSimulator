//
// Created by hadar on 12/29/19.
//

#ifndef FLIGHTSIMULATOR_CONDITION_H
#define FLIGHTSIMULATOR_CONDITION_H

#include "Parser.h"
#include "Interpreter.h"
#include "SymbolTable.h"
#include "Lexer.h"
#include "ex1.h"
#include <iostream>
#include <string>
#include "PrintCommand.h"
#include <string>
#include "Expression.h"
#include "Command.h"

using namespace std;

class Condition : public Command {
private:
    vector <string> condition; // a op b / a
    bool result;
public:
    Condition(vector <string> cond);
    bool getResult();
    void execute(int *it);

};
#endif //FLIGHTSIMULATOR_CONDITION_H
