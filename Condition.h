//
// Created by hadar on 12/29/19.
//

#ifndef FLIGHTSIMULATOR_CONDITION_H
#define FLIGHTSIMULATOR_CONDITION_H

#include "Parser.h"
#include "Interpreter.h"
#include "Lexer.h"
#include "ex1.h"
#include <string>

class Condition : public Command {
private:
    vector <string> condition; // a op b / a
    bool result;
public:

    virtual void execute(int &it);

};
#endif //FLIGHTSIMULATOR_CONDITION_H
