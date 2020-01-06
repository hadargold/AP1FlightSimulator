//
// Created by hadar on 12/27/19.
//

#ifndef FLIGHTSIMULATOR_WHILECOMMAND_H
#define FLIGHTSIMULATOR_WHILECOMMAND_H

#include <string>
#include "Condition.h"
#include "CommandsManager.h"
#include "UpdateValCommand.h"

//class IfCommand : public Condition{
class WhileCommand : public Command{
    int iter;
    vector <string> lex;
    SymbolTable *symbolTable;
    CommandsManager* commandsManager;
public:
    WhileCommand(vector <string> lexer, int i, SymbolTable *symbolTable, CommandsManager* commandsManager);
    void doCommand(vector<string> &text);
    void execute(int *index);
    bool calcResult(vector<string> conditionVec);
    bool getResult(vector<string> conditionVec);
};


#endif //FLIGHTSIMULATOR_WHILECOMMAND_H

