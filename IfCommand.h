//
// Created by hadar on 12/27/19.
//

#ifndef FLIGHTSIMULATOR_IFCOMMAND_H
#define FLIGHTSIMULATOR_IFCOMMAND_H


#include "Condition.h"
#include "CommandsManager.h"

class IfCommand : Condition {
    vector<string>::iterator &it;
public:
    void doCommand(vector<string> &text);
};


#endif //FLIGHTSIMULATOR_IFCOMMAND_H