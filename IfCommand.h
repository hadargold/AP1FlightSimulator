//
// Created by hadar on 12/27/19.
//

#ifndef FLIGHTSIMULATOR_IFCOMMAND_H
#define FLIGHTSIMULATOR_IFCOMMAND_H

#include <string>
#include "Condition.h"
#include "CommandsManager.h"

class IfCommand : Condition {
    //vector<string>::iterator &it;
    vector<string> conditionVec;
    int iter;
    vector <string> lex;
public:
    IfCommand(string a, string op, string b, int i);
    void doCommand(vector<string> &text);
};


#endif //FLIGHTSIMULATOR_IFCOMMAND_H