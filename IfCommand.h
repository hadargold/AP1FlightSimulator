//
// Created by hadar on 12/27/19.
//

#ifndef FLIGHTSIMULATOR_IFCOMMAND_H
#define FLIGHTSIMULATOR_IFCOMMAND_H

#include <string>
#include "Condition.h"
#include "CommandsManager.h"
#include "UpdateValCommand.h"

//class IfCommand : public Condition{
class IfCommand : public Command{
    //vector<string>::iterator &it;
    //vector<string> conditionVec;
    int iter;
    vector <string> lex;
    SymbolTable *symbolTable;
public:
    IfCommand(vector <string> lexer, int i, SymbolTable *symbolTable);
//    explicit IfCommand(int i ,vector <string> lexer) {
//        this->iter = i;
//        this->lex = lexer; // check * !!!!!
//    }
    void doCommand(vector<string> &text);
    void execute(int *index);
};


#endif //FLIGHTSIMULATOR_IFCOMMAND_H
